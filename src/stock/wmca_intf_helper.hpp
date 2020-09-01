#pragma once

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>

class WmcaIntfHelper {
private:
	const wchar_t* pClassName;
	const wchar_t* pWindowName;
	HINSTANCE hInstance;
public:
	WmcaIntfHelper(const wchar_t* pClassName, const wchar_t* pWindowName);
	~WmcaIntfHelper() = default;
	ATOM registerWndClass(WNDPROC wndClass);
	HWND initInstance();
	int messageLoop();
};

