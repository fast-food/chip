#ifndef COMMUNICATOR
#define COMMUNICATOR

#include <stdlib.h>
#include <string.h>
#include <nfc/nfc.h>
#include <vector>
#include <iostream>

#include "nfcUtils.h"
#include "apduCmd.h"
#include "apduResp.h"

class NfcManager {
    private:
        nfc_context* mNfcContext;
        nfc_device* mNfcDevice;
        nfc_modulation mNfcModulation;

    public:
        NfcManager();

        bool open();
        void close();
        bool isTargetPresent();
        bool transceive(const APDUCmd& capdu, APDUResp& rapdu);
        bool selectApplication(const std::string& appId, APDUResp& rapdu);
};

#endif
