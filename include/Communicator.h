#ifndef DEF_COMMUNICATOR
#define DEF_COMMUNICATOR

#include <stdlib.h>
#include <string.h>
#include <nfc/nfc.h>

#include <vector>
#include "Utils.h"

class Communicator {
    private:
        nfc_device* m_nfcDevice;
        nfc_target m_nfcTarget;
        nfc_context *m_nfcContext;
        nfc_modulation m_nfcModulation;

        uint8_t *m_apduCommand;
        uint8_t *m_apduResponse;
        size_t m_apduLength;

        std::string m_appId;

    public:
        Communicator();
        ~Communicator();

        bool open();
        void close();

        bool isTargetPresent();
        bool selectApplication(std::string appId);
        bool send(const std::string &message, std::string &response);
};

#endif
