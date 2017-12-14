#include "../include/Communicator.h"

Communicator::Communicator(){
    m_capdulen = 0;
    m_rapdulen = MAX_DATA_LENGTH;
    m_capdu = static_cast<uint8_t*>(malloc(MAX_DATA_LENGTH));
    m_rapdu = static_cast<uint8_t*>(malloc(MAX_DATA_LENGTH));
}

Communicator::~Communicator(){
    free(m_capdu);
    free(m_rapdu);
}

bool Communicator::open(){
    nfc_init(&m_nfcContext);
    if (m_nfcContext == NULL) {
        return false;
    }

    m_nfcDevice = nfc_open(m_nfcContext, NULL);
    if(m_nfcDevice == NULL){
        return false;
    }

    m_nfcModulation = {
       .nmt = NMT_ISO14443A,
       .nbr = NBR_106,
    };
}

void Communicator::close(){
    nfc_close(m_nfcDevice);
    nfc_exit(m_nfcContext);
}

bool Communicator::isTargetPresent(){
    return (nfc_initiator_select_passive_target(m_nfcDevice, m_nfcModulation, NULL, 0, &m_nfcTarget)>0);
}

bool Communicator::selectApplication(std::string appId, std::string &response){
    std::vector<uint8_t> selectApdu = hexStringToByteArray("00A40400");
    std::vector<uint8_t> appIdHex = hexStringToByteArray(appId);
    selectApdu.push_back((uint8_t)appIdHex.size());
    selectApdu.insert(selectApdu.end(), appIdHex.begin(), appIdHex.end());

    uint8_t *cmd = &selectApdu[0];
    m_capdulen = selectApdu.size();
    memcpy(m_capdu, cmd, m_capdulen);

    int res = nfc_initiator_transceive_bytes(m_nfcDevice, m_capdu, m_capdulen, m_rapdu, m_rapdulen, 500);
    if(res<0){
        return false;
    }

    if(res<2 || m_rapdu[res-2] != 0x90 || m_rapdu[res-1] != 0x00){
        return false;
    }

    response = byteArrayToString(m_rapdu, 0, res-2);
    return true;
}

bool Communicator::send(const std::string &message, std::string &response){
    if(message.size()>MAX_DATA_LENGTH){
        return false;
    }

    std::vector<uint8_t> apduCmd(message.begin(), message.end());
    uint8_t *cmd = &apduCmd[0];
    m_capdulen = apduCmd.size();
    memcpy(m_capdu, cmd, m_capdulen);

    int res = nfc_initiator_transceive_bytes(m_nfcDevice, m_capdu, m_capdulen, m_rapdu, m_rapdulen, 500);
    if (res<0) {
        return false;
    }

    if(res<2 || m_rapdu[res-2] != 0x90 || m_rapdu[res-1] != 0x00){
        return false;
    }

    response = byteArrayToString(m_rapdu, 0, res-2);
    return true;
}
