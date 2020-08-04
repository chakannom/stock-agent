// WmcaIntf.h: interface for the WmcaIntf class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WMCAINTF_HPP
#define WMCAINTF_HPP

#include <windows.h>

typedef BOOL (__stdcall TLoad               )();
typedef BOOL (__stdcall TFree               )();
typedef BOOL (__stdcall TSetServer          )(const char* szServer);
typedef BOOL (__stdcall TSetPort            )(const int nPort);
typedef BOOL (__stdcall TIsConnected        )();
typedef BOOL (__stdcall TConnect            )(HWND hWnd,DWORD dwMsg,char cMediaType,char cUserType,const char* pszID,const char* pszPassword,const char* pszSignPassword);
typedef BOOL (__stdcall TDisconnect         )();
typedef BOOL (__stdcall TTransact           )(HWND hWnd,int nTransactionID,const char* pszTrCode,const char* pszInputData,int nInputDataSize,int nHeaderType,int nAccountIndex);
typedef BOOL (__stdcall TQuery              )(HWND hWnd,int nTransactionID,const char* pszTrCode,const char* pszInputData,int nInputDataSize,int nAccountIndex);
typedef BOOL (__stdcall TRequest            )(HWND hWnd,int nTransactionID,const char* pszTrCode,const char* pszInputData,int nInputDataSize,const char* pszOpenBranchCode);
typedef BOOL (__stdcall TAttach             )(HWND hWnd,const char* pszSiseName,const char* pszInputCode,int nInputCodeSize,int nInputCodeTotalSize);
typedef BOOL (__stdcall TDetach             )(HWND hWnd,const char* pszSiseName,const char* pszInputCode,int nInputCodeSize,int nInputCodeTotalSize);
typedef BOOL (__stdcall TDetachWindow       )(HWND hWnd);
typedef BOOL (__stdcall TDetachAll          )();
typedef BOOL (__stdcall TSetOption          )(const char* szKey,const char* szValue);
typedef BOOL (__stdcall TSetAccountIndexPwd )(const char* pszHashOut,int nAccountIndex,const char* pszPassword); 
typedef BOOL (__stdcall TSetOrderPwd        )(const char* pszHashOut,const char* pszPassword);
typedef BOOL (__stdcall TSetHashPwd         )(const char* pszHashOut,const char* pszKey,const char* pszPassword);
typedef BOOL (__stdcall TSetAccountNoPwd    )(const char* pszHashOut,const char* pszAccountNo,const char* pszPassword);
typedef BOOL (__stdcall TSetAccountNoByIndex)(const char* pszHashOut,int nAccountIndex);

//----------------------------------------------------------------------//
// wmca.dll wrapping functions
//----------------------------------------------------------------------//

class WmcaIntf
{
private:
    HINSTANCE               m_hDll;

    TLoad                   *m_pLoad;
    TFree                   *m_pFree;
    TSetServer              *m_pSetServer;
    TSetPort                *m_pSetPort;
    TIsConnected            *m_pIsConnected;
    TConnect                *m_pConnect;
    TDisconnect             *m_pDisconnect;
    TTransact               *m_pTransact;
    TQuery                  *m_pQuery;   
    TRequest                *m_pRequest;
    TAttach                 *m_pAttach;
    TDetach                 *m_pDetach;
    TDetachWindow           *m_pDetachWindow;
    TDetachAll              *m_pDetachAll;
    TSetOption              *m_pSetOption;
    TSetAccountIndexPwd     *m_pSetAccountIndexPwd;
    TSetOrderPwd            *m_pSetOrderPwd;
    TSetHashPwd             *m_pSetHashPwd;
    TSetAccountNoPwd        *m_pSetAccountNoPwd;
    TSetAccountNoByIndex    *m_pSetAccountNoByIndex;

public:
    WmcaIntf();
    virtual ~WmcaIntf();

public:
    BOOL Load               ();
    BOOL Free               ();
    BOOL Connect            (HWND hWnd, DWORD msg, char MediaType,char UserType,const char* szID,const char* szPW, const char* szCertPW);  // ?��?��?�� ?���? �? ?��?��
    BOOL Disconnect         ();
    BOOL SetServer          (const char* szServer);  // ?��?��?���? �??��(?��?��?��)
    BOOL SetPort            (int port);  // ?��?��?��?�� �??��(?��?��?��)
    BOOL IsConnected        ();
    BOOL Transact           (HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nHeadType=0, int nAccountIndex=0);  // ?��?���? 방�???��?���? Transact()????��
    BOOL Query              (HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nAccountIndex=0);  // Query()?��?���? ?��?��?��?��?��.
    BOOL Request            (HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, const char* szOpenBranchCode=NULL);
    BOOL Attach             (HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen);  // ?��?���? ?��?�� ?���?
    BOOL Detach             (HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen);  // ?��?���? ?��?�� 취소
    BOOL DetachWindow       (HWND hWnd);  // ?��?���? ?��?�� ?��괄취?��(?��?��?��?��?��)
    BOOL DetachAll          ();  // ?��?���? ?��?�� ?��괄취?��(?���?)
    BOOL SetOption          (const char* szKey,const char* szValue);
    BOOL SetAccountIndexPwd (const char* pszHashOut,int nAccountIndex,const char* pszPassword);  // 계좌?��?��?�� �? 비�??번호 ?��?��
    BOOL SetOrderPwd        (const char* pszHashOut,const char* pszPassword);  // 거래비�??번호 ?��?��
    BOOL SetAccountNoPwd    (const char* pszHashOut,const char* pszAccountNo,const char* pszPassword);  //계좌번호 �? 비�??번호 ?��?��
    BOOL SetHashPwd         (const char* pszHashOut,const char* pszKey,const char* pszPassword);
    BOOL SetAccountNoByIndex(const char* pszHashOut,int nAccountIndex);  // 계좌?��?��?��?�� ?��?��?��?�� 계좌번호
};


#endif //WMCAINTF_HPP