#include "ExtraWindow.h"
#include "button.h"
//extern ExtraWindow win2;
//ExtraWindow* Procede;
LRESULT CALLBACK NonStaticWindowProcThread(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



	//Button Typer2(1);
void HandleOnThread(ExtraWindow& window)
{

	RegisterClassW(&window.CLS);
	
	// Create the window
	window.Hwnd = CreateWindowW(window.CLS.lpszClassName, window.text.c_str(), WS_OVERLAPPED | 
		WS_CAPTION | 
		WS_SYSMENU | 
		WS_THICKFRAME | WS_VISIBLE, window.x, window.y, window.width, window.height, NULL, NULL, NULL, NULL);
	
	SetWindowLongPtr(window.Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&window));
	
	//Send error message if window creation Failed.
	if (!window.Hwnd)
	{
		MessageBox(NULL,(wstring( L"Failed to ctreate window \"") + window.text + wstring(L"\"please check your code")).c_str(), L"Failure!" , MB_ICONERROR | MB_OK);
		return;
	}
	
	//set correct proc function for "NonStaticWindowProcThread".


	//message loop
	MSG msg;
	while (GetMessage(&msg, window.Hwnd, NULL, NULL)>0)
	{	
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}


}


LRESULT CALLBACK NonStaticWindowProcThread(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	

	ExtraWindow* window = reinterpret_cast<ExtraWindow*>( GetWindowLongPtr(hwnd, GWLP_USERDATA));
	
	
	if (!window)
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
		return window->Proc(window->Hwnd, uMsg, wParam, lParam);
	
}






LRESULT ExtraWindow::Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{


	
	
		//Makes chilwindow backgrounds transparent.
	//case WM_CTLCOLORSTATIC:
	//
	//	SetBkMode(HDC(wp), TRANSPARENT);
	//	return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
	//
	//	break;
	//
	//
	//
	//case WM_CTLCOLOREDIT:
	//
	//	SetBkMode(HDC(wp), TRANSPARENT);
	//	return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
	//
	//	break;

	//case WM_CTLCOLORBTN:
	//	SetBkColor((HDC)wp, RGB(0, 255, 0));
	//	SetBkMode((HDC)wp, TRANSPARENT);
	//	return(LRESULT)CreateSolidBrush(RGB(0,255,0));
	//
	

	case WM_CTLCOLORSTATIC:
	{

		DWORD CtrlID = GetDlgCtrlID((HWND)lp);
		HBRUSH BK = CreateSolidBrush(RGB(ChildColorBK[0], ChildColorBK[1], ChildColorBK[2]));
		HDC hdcStatic = (HDC)wp;
		SetTextColor(hdcStatic, RGB(ChildColorText[0], ChildColorText[1], ChildColorText[2]));
		SetBkColor(hdcStatic, RGB(ChildColorBK[0], ChildColorBK[1], ChildColorBK[2]));
		return (INT_PTR)BK;
	}

	case WM_CTLCOLOREDIT:
	{

		DWORD CtrlID = GetDlgCtrlID((HWND)lp);
		HBRUSH BK = CreateSolidBrush(RGB(EWColorBK[0], EWColorBK[1], EWColorBK[2]));
		HDC hdcStatic = (HDC)wp;
		SetTextColor(hdcStatic, RGB(EWColorText[0], EWColorText[1], EWColorText[2]));
		SetBkColor(hdcStatic, RGB(EWColorBK[0], EWColorBK[1], EWColorBK[2]));
		return (INT_PTR)BK;
	}


	case WM_COMMAND:
		for (int i = 0; i < functionallitys.size(); i++)
		{
			if (functionallitys[i].first == wp)
			{
				functionallitys[i].second();
				break;
			}
		}
		break;



	case WM_USER + 1:

		//handles manipulation of ChildWindows on thread
		if (wp) {
			((ChildWindow*)lp)->place();
			break;
		}
		
			DestroyWindow(((ChildWindow*)lp)->Hwnd);
			break;
		
		break;
	case WM_DESTROY:
		DestroyWindow(hwnd);
	case WM_CLOSE:
		PostQuitMessage(0);


		break;
	}
	return DefWindowProcW(hwnd, msg, wp, lp);
}

ExtraWindow::ExtraWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B, wstring classname) :MainWindow(Text, x, y, width, height)
{
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpszClassName = text.c_str();
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpfnWndProc = NonStaticWindowProcThread;
	functionallitys.reserve(4);
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	
	procthread = std::thread(HandleOnThread,std::ref(*this));
	
	
}



ExtraWindow::~ExtraWindow()
{
	procthread.join();
}



