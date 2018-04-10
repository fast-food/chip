#ifndef COMMUNICATOR
#define COMMUNICATOR

#include <stdlib.h>
#include <string.h>
#include <nfc/nfc.h>
#include <vector>
#include <iostream>

#include "nfcUtils.h"

struct NfcManager {
    static constexpr size_t MAX_DATA_LENGTH = 65535;

    nfc_context* mNfcContext;
    nfc_device* mNfcDevice;
    nfc_modulation mNfcModulation;

    bool open(){
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

    void close(){
        nfc_close(mNfcDevice);
        nfc_exit(mNfcContext);
    }

    std::string getDeviceName(){
        return nfc_device_get_name(mNfcDevice);
    }

    std::string getNfcLibVersion(){
        return nfc_version();
    }

    bool isTargetPresent(){
        nfc_target nfcTarget;
        return (nfc_initiator_select_passive_target(mNfcDevice, mNfcModulation, NULL, 0, &nfcTarget)>0);
    }

    bool selectApplication(std::string appId, std::string &response){
        std::vector<uint8_t> selectApdu = hexStringToByteArray("00A40400");
        std::vector<uint8_t> appIdHex = hexStringToByteArray(appId);
        selectApdu.push_back((uint8_t)appIdHex.size());
        selectApdu.insert(selectApdu.end(), appIdHex.begin(), appIdHex.end());

        uint8_t *capdu = &selectApdu[0];
        size_t capdulen = selectApdu.size();
        uint8_t rapdu[3];
        size_t rapdulen = 3;

        int res = nfc_initiator_transceive_bytes(mNfcDevice, capdu, capdulen, rapdu, rapdulen, 500);
        if(res<0){
            return false;
        }

        if(res<2 || rapdu[res-2] != 0x90 || rapdu[res-1] != 0x00){
            return false;
        }

        response = byteArrayToString(rapdu, 0, res-2);
        return true;
    }

    bool send(const std::string &message, std::string &response){
        std::vector<uint8_t> apduCmd(message.begin(), message.end());
        uint8_t *capdu = &apduCmd[0];
        size_t capdulen = apduCmd.size();
        uint8_t rapdu[3];
        size_t rapdulen = 3;

        int res = nfc_initiator_transceive_bytes(mNfcDevice, capdu, capdulen, rapdu, rapdulen, 500);
        if (res<0) {
            return false;
        }

        if(res<2 || rapdu[res-2] != 0x90 || rapdu[res-1] != 0x00){
            return false;
        }

        response = byteArrayToString(rapdu, 0, res-2);
        return true;
    }
};

#endif
