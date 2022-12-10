#pragma once
#include "Window.h"

LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg)
	{
	case WM_COMMAND:

		switch (wp)
		{
		case 1:
			MessageBeep(MB_OK);
			break;
		case 2:
			MessageBox(hwnd, L" you sure???", L"L", MB_YESNO);
			break;
		case 3:

			break;
		case 4:
			break;

		case 5:
			





			break;

		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hwnd, msg, wp, lp);
	}
	return DefWindowProcW(hwnd, msg, wp, lp);

}

class MainWindow: public Window
{
	 WNDCLASSW CLS = { WS_OVERLAPPEDWINDOW | WS_VISIBLE ,Proc ,0,0,GetModuleHandle(NULL),0, LoadCursor(NULL, IDC_ARROW),(HBRUSH)COLOR_DESKTOP,0,L"WNDCLS" };

};

