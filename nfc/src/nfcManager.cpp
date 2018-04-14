#include "../include/nfcManager.h"

NfcManager::NfcManager(){
    mNfcContext = NULL;
    mNfcDevice = NULL;
}

bool NfcManager::open(){
    nfc_init(&mNfcContext);
    if (mNfcContext == NULL) {
        return false;
    }

    mNfcDevice = nfc_open(mNfcContext, NULL);
    if(mNfcDevice == NULL){
        return false;
    }

    if(nfc_initiator_init(mNfcDevice) < 0) {
        return false;
    }

    mNfcModulation = {
       .nmt = NMT_ISO14443A,
       .nbr = NBR_106,
    };

    return true;
}

void NfcManager::close(){
    nfc_close(mNfcDevice);
    nfc_exit(mNfcContext);
}

bool NfcManager::isTargetPresent(){
    nfc_target nfcTarget;
    return (nfc_initiator_select_passive_target(mNfcDevice, mNfcModulation, NULL, 0, &nfcTarget)>0);
}

bool NfcManager::transceive(const APDUCmd& cmd, APDUResp& resp){
    std::vector<uint8_t> cmdApdu = cmd.build();
    uint8_t *capdu = &cmdApdu[0];
    size_t capdulen = cmdApdu.size();
    uint8_t rapdu[APDUResp::MAX_APDU_LENGTH];
    size_t rapdulen = APDUResp::MAX_APDU_LENGTH;

    int res = nfc_initiator_transceive_bytes(mNfcDevice, capdu, capdulen, rapdu, rapdulen, 700);
    if(res<0){
        return false;
    }

    if(res<2 || rapdu[res-2] != 0x90 || rapdu[res-1] != 0x00){
        return false;
    }

    resp.setSW1(0x90);
    resp.setSW2(0x00);
    resp.setData(rapdu, res-2);
    return true;
}

bool NfcManager::selectApplication(const std::string& appId, APDUResp& rapdu){
    APDUCmd capdu;
    capdu.setClass(0x00);
    capdu.setInstruction(0xA4);
    capdu.setParams(0x04, 0x00);
    capdu.setData(hexStringToByteArray(appId));
    capdu.updateDataLength();
    capdu.setExpectedLength(0);
    return transceive(capdu, rapdu);
}
