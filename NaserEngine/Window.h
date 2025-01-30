#pragma once
#include "Prerequisites.h"

class
	Window {
public:
	Window() = default;
	~Window() = default;

	HRESULT
		init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);

	void
		update();

	void
		render();

	void
		destroy();

public:
	HINSTANCE m_hInst = nullptr;
	HWND m_hWnd = nullptr;
	unsigned int m_width;
	unsigned int m_height;
	RECT m_rect;
	std::string m_windowName = "Naser Engine";
private:

	
};