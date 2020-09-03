#include <string>
#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>


#include "wmca_intf_msg_event.hpp"

WmcaIntfMsgEvent::WmcaIntfMsgEvent(std::wstring* pMsg) {
    this->pMsg = pMsg;
}

int WmcaIntfMsgEvent::OnWmcaEvent(WPARAM dwMessageType, LPARAM lParam) {
    switch (dwMessageType) {
        case CA_CONNECTED:          //로그인 성공
            OnWmConnected((LOGINBLOCK*)lParam);
            break;
        case CA_DISCONNECTED:        //접속 끊김
            OnWmDisconnected();
            break;
        case CA_SOCKETERROR:        //통신 오류 발생
            OnWmSocketError((int)lParam);
            break;
        case CA_RECEIVEDATA:        //서비스 응답 수신(TR)
            OnWmReceiveData((OUTDATABLOCK*)lParam);
            break;
        case CA_RECEIVESISE:        //실시간 데이터 수신(BC)
            OnWmReceiveSise((OUTDATABLOCK*)lParam);
            break;
        case CA_RECEIVEMESSAGE:     //상태 메시지 수신 (입력값이 잘못되었을 경우 문자열형태로 설명이 수신됨)
            OnWmReceiveMessage((OUTDATABLOCK*)lParam);
            break;
        case CA_RECEIVECOMPLETE:    //서비스 처리 완료
            OnWmReceiveComplete((OUTDATABLOCK*)lParam);
            break;
        case CA_RECEIVEERROR:       //서비스 처리중 오류 발생 (입력값 오류등)
            OnWmReceiveError((OUTDATABLOCK*)lParam);
            break;
        default:
            break;
    }
    return 0;
}

void WmcaIntfMsgEvent::OnWmConnected(LOGINBLOCK* pLogin) {
    // 로그인이 성공하면, 접속시각 및 계좌번호 정보를 받아 적절히 보관/출력합니다.
    // 계좌번호에 대한 순서(인덱스)는 계좌관련 서비스 호출시 사용되므로 중요합니다.

    //접속시각 출력
    char szText[256] = { 0 };
    strncpy(szText, pLogin->pLoginInfo->szDate, sizeof pLogin->pLoginInfo->szDate);
    std::string	strText = "접속시각 : ";
    strText += szText;
    pMsg->append(L"접속시각 : " + std::wstring(strText.begin(), strText.end()) + L" || ");

    //계좌번호 출력
    char szAccountCount[8] = { 0 };
    strncpy(szAccountCount, pLogin->pLoginInfo->szAccountCount, sizeof pLogin->pLoginInfo->szAccountCount);
    int nAccountCount = atoi(szAccountCount);
    pMsg->append(L"계좌번호: [ ");

    for (int i = 0; i < nAccountCount; i++) {
        char szAccountNo[16] = { 0 };
        strncpy(szAccountNo, (char*)&pLogin->pLoginInfo->accountlist[i].szAccountNo, sizeof pLogin->pLoginInfo->accountlist[i].szAccountNo);

        std::string strAccountNo(szAccountNo);
        pMsg->append(std::wstring(strAccountNo.begin(), strAccountNo.end()) + L',');
    }

    pMsg->append(L" ] || ");

    pMsg->append(L"정상 접속되었습니다 || ");
}

void WmcaIntfMsgEvent::OnWmDisconnected() {
    pMsg->append(L"접속이 끊겼습니다 || ");
}

void WmcaIntfMsgEvent::OnWmSocketError(int socketErrorCode) {
    pMsg->append(L"통신오류발생 || ");
}

void WmcaIntfMsgEvent::OnWmReceiveData(OUTDATABLOCK* pOutData) {

}

void WmcaIntfMsgEvent::OnWmReceiveSise(OUTDATABLOCK* pSiseData) {

}

void WmcaIntfMsgEvent::OnWmReceiveMessage(OUTDATABLOCK* pMessage) {
    MSGHEADER* pMsgHeader = (MSGHEADER*)pMessage->pData->szData;
    std::wstring wstrTrIndex(std::to_wstring(pMessage->TrIndex));
    // pMsgHeader->msg_cd
    std::wstring wstrMsgCd;
    int lenStrMsgCd = -1;
    int nCharsStrMsgCd = MultiByteToWideChar(CP_ACP, 0, pMsgHeader->msg_cd, lenStrMsgCd, NULL, 0);
    wstrMsgCd.resize(nCharsStrMsgCd);
    MultiByteToWideChar(CP_ACP, 0, pMsgHeader->msg_cd, lenStrMsgCd, const_cast<wchar_t*>(wstrMsgCd.c_str()), nCharsStrMsgCd);
    // pMsgHeader->user_msg
    std::wstring wstrUserMsg;
    int lenStrUserMsg = -1;
    int nCharsStrUserMsg = MultiByteToWideChar(CP_ACP, 0, pMsgHeader->user_msg, lenStrUserMsg, NULL, 0);
    wstrMsgCd.resize(nCharsStrUserMsg);
    MultiByteToWideChar(CP_ACP, 0, pMsgHeader->user_msg, lenStrUserMsg, const_cast<wchar_t*>(wstrMsgCd.c_str()), nCharsStrUserMsg);

    pMsg->append(L"[" + wstrTrIndex + L"] " + wstrMsgCd + L" : " + wstrUserMsg + L" || ");
}

void WmcaIntfMsgEvent::OnWmReceiveComplete(OUTDATABLOCK* pOutData) {
    //TR 호출 완료시점에 뭔가 해야한다면 아래와 같이 처리할 수 있습니다
    switch (pOutData->TrIndex) {
        case TRID_c1101:
            pMsg->append(L"주식 현재가 조회 완료");
            break;
        case TRID_c8201:
            pMsg->append(L"계좌 잔고 조회 완료");
            break;
    }
}

void WmcaIntfMsgEvent::OnWmReceiveError(OUTDATABLOCK* pError) {
    //서비스 호출이 실패할 경우 수신됨
    pMsg->append(L"*** ERROR ***");
    std::string strText(pError->pData->szData);
    pMsg->append(std::wstring(strText.begin(), strText.end()));
}