#ifndef APDUCMD
#define APDUCMD

#include <vector>
#include <cstdint>
#include <string>
#include <cassert>

#include "nfcUtils.h"

class APDUCmd {
    private:
        uint8_t mCla;
        uint8_t mIns;
        std::vector<uint8_t> mParams;
        std::vector<uint8_t> mLc;
        std::vector<uint8_t> mData;
        std::vector<uint8_t> mLe;

        std::vector<uint8_t> intToBytes(const int& value);
        void setCommandLength();

    public:
        APDUCmd();

        void setClass(const uint8_t& cla);
        void setInstruction(const uint8_t& ins);
        void setParams(const uint8_t& p1, const uint8_t& p2);
        void setData(const std::string& data);
        void setData(const std::vector<uint8_t>& data);
        void setExpectedLength(const int& length);

        uint8_t getClass() const;
        uint8_t getInstruction() const;
        std::vector<uint8_t> getParams() const;
        std::string getData() const;

        std::vector<uint8_t> build() const;

        static const size_t MAX_CMD_LENGTH = 255;
        static const size_t MAX_APDU_LENGTH = MAX_CMD_LENGTH + 6;
};

#endif
