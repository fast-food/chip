#ifndef APDURESP
#define APDURESP

#include <vector>
#include <cstdint>
#include <string>
#include <cassert>

#include "apduCmd.h"
#include "nfcUtils.h"

class APDUResp {
    private:
        uint8_t mSW1;
        uint8_t mSW2;
        std::vector<uint8_t> mResp;

    public:
        APDUResp();

        void setSW1(const uint8_t& SW1);
        void setSW2(const uint8_t& SW2);
        void setData(const std::string& response);
        void setData(const uint8_t* resp, const size_t& length);

        uint8_t getSW1() const;
        uint8_t getSW2() const;
        std::string getStringData() const;
        std::vector<uint8_t> getBytesData() const;

        std::vector<uint8_t> build() const;

        static const size_t MAX_RESP_LENGTH = APDUCmd::MAX_CMD_LENGTH + 1;
        static const size_t MAX_APDU_LENGTH = MAX_RESP_LENGTH + 6;
};

#endif
