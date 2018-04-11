#ifndef COMMUNICATOR
#define COMMUNICATOR

#include <stdlib.h>
#include <string.h>
#include <nfc/nfc.h>
#include <vector>
#include <iostream>

#include "nfcUtils.h"

class NfcManager {
    private:
        const size_t MAX_DATA_LENGTH = 65535;
        nfc_context* mNfcContext;
        nfc_device* mNfcDevice;
        nfc_modulation mNfcModulation;

    public:
        NfcManager();

        bool open();
        void close();
        std::string getDeviceName();
        std::string getNfcLibVersion();
        bool isTargetPresent();
        bool transceive(std::vector<uint8_t>& apdu, std::string& response);
        bool selectApplication(std::string appId, std::string &response);
        bool send(const std::string &message, std::string &response);
};

#endif
