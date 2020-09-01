#pragma once

class WmcaIntfMsgProc {
public:
    class ObjectMsg {
    public:
        int statusCode;
    };
    class ResultMsg : public ObjectMsg {
    public:
        std::wstring msg;
    };
public:
    // Connect
    static ResultMsg connectMsg;
    static WNDPROC connectWndProc;
    // Sample
    static std::wstring sampleData;
    static WNDPROC sampleWndProc;

};

