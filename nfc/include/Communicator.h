#ifndef DEF_COMMUNICATOR
#define DEF_COMMUNICATOR

#include <stdlib.h>
#include <string.h>
#include <nfc/nfc.h>

#include <vector>
#include "NfcUtils.h"

class Communicator {
    private:
        nfc_device* m_nfcDevice;
        nfc_target m_nfcTarget;
        nfc_context *m_nfcContext;
        nfc_modulation m_nfcModulation;

        static constexpr size_t MAX_DATA_LENGTH = 65535;

    public:
        Communicator();
        ~Communicator();

        bool open();
        void close();

        bool isTargetPresent();
        bool selectApplication(std::string appId, std::string &response);
        bool send(const std::string &message, std::string &response);
};

#endif
