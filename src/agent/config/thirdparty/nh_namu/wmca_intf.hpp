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
    BOOL Connect            (HWND hWnd, DWORD msg, char MediaType,char UserType,const char* szID,const char* szPW, const char* szCertPW);  // ?¬?©? ?Έμ¦? λ°? ? ?
    BOOL Disconnect         ();
    BOOL SetServer          (const char* szServer);  // ? ??λ²? μ§?? (???)
    BOOL SetPort            (int port);  // ? ??¬?Έ μ§?? (???)
    BOOL IsConnected        ();
    BOOL Transact           (HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nHeadType=0, int nAccountIndex=0);  // ?€?λ₯? λ°©μ???? €λ©? Transact()???? 
    BOOL Query              (HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, int nAccountIndex=0);  // Query()?¨?λ₯? ?¬?©??Έ?.
    BOOL Request            (HWND hWnd, int nTRID, const char* szTRCode, const char* szInput, int nInputLen, const char* szOpenBranchCode=NULL);
    BOOL Attach             (HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen);  // ?€?κ°? ??Έ ?μ²?
    BOOL Detach             (HWND hWnd, const char* szBCType, const char* szInput, int nCodeLen, int nInputLen);  // ?€?κ°? ??Έ μ·¨μ
    BOOL DetachWindow       (HWND hWnd);  // ?€?κ°? ??Έ ?Όκ΄μ·¨?(???°?¨?)
    BOOL DetachAll          ();  // ?€?κ°? ??Έ ?Όκ΄μ·¨?(? μ²?)
    BOOL SetOption          (const char* szKey,const char* szValue);
    BOOL SetAccountIndexPwd (const char* pszHashOut,int nAccountIndex,const char* pszPassword);  // κ³μ’?Έ?±?€ λ°? λΉλ??λ²νΈ ?? ₯
    BOOL SetOrderPwd        (const char* pszHashOut,const char* pszPassword);  // κ±°λλΉλ??λ²νΈ ?? ₯
    BOOL SetAccountNoPwd    (const char* pszHashOut,const char* pszAccountNo,const char* pszPassword);  //κ³μ’λ²νΈ λ°? λΉλ??λ²νΈ ?? ₯
    BOOL SetHashPwd         (const char* pszHashOut,const char* pszKey,const char* pszPassword);
    BOOL SetAccountNoByIndex(const char* pszHashOut,int nAccountIndex);  // κ³μ’?Έ?±?€? ?΄?Ή?? κ³μ’λ²νΈ
};


#endif //WMCAINTF_HPP