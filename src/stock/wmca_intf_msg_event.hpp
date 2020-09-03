#pragma once

#include <stock/wmca_intf.hpp>

class WmcaIntfMsgEvent {
private:
    static const int TRID_c1101 = 1;
    static const int TRID_c8201 = 2;
    static const int TRID_c8102 = 3;
    std::wstring* pMsg;
public:
    WmcaIntfMsgEvent(std::wstring* pMsg);
    ~WmcaIntfMsgEvent() = default;
private: // 하위 함수 public가 되거나 없어지거나 해야함 (아래 함수들 테스트 경과에 따라서)
    int OnWmcaEvent(WPARAM dwMessageType, LPARAM lParam);
//private: // 하위 함수 private가 될 수도 있음(테스트가 필요함)
public:
    void OnWmConnected(LOGINBLOCK* pLogin);
    void OnWmDisconnected();
    void OnWmSocketError(int socketErrorCode);
    void OnWmReceiveData(OUTDATABLOCK* pOutData);
    void OnWmReceiveSise(OUTDATABLOCK* pSiseData);
    void OnWmReceiveMessage(OUTDATABLOCK* pMessage);
    void OnWmReceiveComplete(OUTDATABLOCK* pOutData);
    void OnWmReceiveError(OUTDATABLOCK* pError);
};

