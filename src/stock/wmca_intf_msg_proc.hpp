#pragma once

#include <stock/wmca_intf_msg_event.hpp>

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
    static WmcaIntfMsgEvent connectMsgEvent;
    static WNDPROC connectWndProc;
    // Disconnect
    static ResultMsg disconnectMsg;
    static WmcaIntfMsgEvent disconnectMsgEvent;
    static WNDPROC disconnectWndProc;
    // Sample
    static std::wstring sampleData;
    static WmcaIntfMsgEvent sampleMsgEvent;
    static WNDPROC sampleWndProc;

};

