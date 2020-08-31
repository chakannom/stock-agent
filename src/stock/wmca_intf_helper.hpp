#pragma once

#include <stock/wmca_intf.hpp>

class WmcaIntfHelper {
public:
	static WNDPROC sampleWndProc;
	static std::wstring sampleData;
private:
	const wchar_t* pClassName;
	const wchar_t* pWindowName;
	HINSTANCE hInstance;
public:
	WmcaIntfHelper(const wchar_t* pClassName, const wchar_t* pWindowName);
	~WmcaIntfHelper() = default;
	ATOM RegisterWndClass(WNDPROC wndClass);
	HWND InitInstance();
	int messageLoop();

	static void generateWndProcFunctions();
};

