#include "../include/Communicator.h"

Communicator::Communicator(){
    m_apduLength = 264;
    m_apduCommand = static_cast<uint8_t*>(malloc(m_apduLength));
    m_apduResponse = static_cast<uint8_t*>(malloc(m_apduLength));
}

Communicator::~Communicator(){
    free(m_apduCommand);
    free(m_apduResponse);
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

bool Communicator::selectApplication(std::string appId){
    std::vector<uint8_t> selectApdu = hexStringToByteArray("00A40400");
    std::vector<uint8_t> appIdHex = hexStringToByteArray(appId);
    selectApdu.push_back((uint8_t)appIdHex.size());
    selectApdu.insert(selectApdu.end(), appIdHex.begin(), appIdHex.end());

    uint8_t *cmd = &selectApdu[0];
    int apduCommandLength=selectApdu.size();
    memcpy(m_apduCommand, cmd, apduCommandLength);

    int res = nfc_initiator_transceive_bytes(m_nfcDevice, m_apduCommand, apduCommandLength, m_apduResponse, m_apduLength, 500);
    if(res<0){
        return false;
    }

    if(res<2 || m_apduResponse[res-2] != 0x90 || m_apduResponse[res-1] != 0x00){
        return false;
    }

    return true;
}

bool Communicator::send(const std::string &message, std::string &response){
    std::vector<uint8_t> apduCmd = stringToByteArray(message);
    uint8_t *cmd = &apduCmd[0];
    int apduCommandLength=apduCmd.size();
    memcpy(m_apduCommand, cmd, apduCommandLength);

    for (int i=0 ; i<apduCmd.size() ; i++) {
        printf("%02x ", cmd[i]);
    }
    printf("\n");

    int res = nfc_initiator_transceive_bytes(m_nfcDevice, m_apduCommand, apduCommandLength, m_apduResponse, m_apduLength, 500);
    if (res<0) {
        return false;
    }

    if(res<2 || m_apduResponse[res-2] != 0x90 || m_apduResponse[res-1] != 0x00){
        return false;
    }

    std::stringstream ss;
    for(unsigned int i=0 ; i<res-2 ; i++){
        ss << m_apduResponse[i];
    }
    response = ss.str();
    return true;
}
