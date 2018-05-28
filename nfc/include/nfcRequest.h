#ifndef NFC_REQUEST
#define NFC_REQUEST

#include <string>
#include <vector>
#include <utility>

class NfcRequest {
    private:
        int mType;
        std::string mUrl;
        std::vector<std::pair<std::string, std::string> > mData;

    public:
        NfcRequest();
        NfcRequest(int type, std::string url);

        int getType() const;
        std::string getUrl() const;
        std::vector<std::pair<std::string, std::string> > getDatas() const;

        void addData(std::string key, std::string value);
        void resetData();
        void setUrl(std::string url);
        void setType(int type);
};

#endif
