#include "MainWindow.h"
//should change this to unordered_map


HDC hdcStatic;
LRESULT MainWindow::Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{

	case WM_CTLCOLORSTATIC:
		//if (ColoredStatic)
		//{
		//	hdcStatic = GetDlgItem(hwnd, 0);
			SetTextColor(hdcStatic, RGB(255, 0, 0));
			//SetBkColor(hdcStatic, RGB(0, 0, 0));
			break;
		//}
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
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, msg, wp, lp);

}
LRESULT CALLBACK NonStaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MainWindow* window = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (window)
	{
		return window->Proc(hwnd, uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}




MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height):Window(Text, x, y, width, height)
{
	
	 CLS.hbrBackground = HBRUSH(COLOR_DESKTOP);
	 CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	 CLS.hInstance = GetModuleHandle(NULL);
	 CLS.lpszClassName = L"WNDCLS";
	 CLS.lpfnWndProc = NonStaticWindowProc;
	 
	 functionallitys.reserve(4);
	RegisterClassW(&CLS);
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	Hwnd = CreateWindow(L"WNDCLS", Text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	

}

MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B):Window(Text, x, y, width, height)
{
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpszClassName = L"WNDCLS";
	CLS.lpfnWndProc = NonStaticWindowProc;
	functionallitys.reserve(4);
	RegisterClassW(&CLS);
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	Hwnd = CreateWindow(L"WNDCLS", Text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));



}

void MainWindow::AddMenu(const wstring& name, long id, bool parent)
{
	if (parent)
	{
		ChildMenus.push_back(  CreateMenu());
		AppendMenuW(menu, MF_POPUP, (UINT_PTR) ChildMenus.back(), name.c_str());
	}
	else
		AppendMenuW(menu, MF_STRING, id, name.c_str());
	SetMenu(Hwnd,  menu);
	
}

bool MainWindow::AddSubMenu(const wstring& name, int menuindex, long id)
{
	if (ChildMenus.size()<menuindex) return false;
	AppendMenu(ChildMenus[menuindex], MF_STRING, id, name.c_str());
	return true;
}

void MainWindow::RemoveMenuBar()
{
	SetMenu(Hwnd, NULL);

}


void MainWindow::start()
{

	MSG msg;
	
	while (GetMessage(&msg, Hwnd, NULL, NULL) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

bool MainWindow::AddFunc(int id, void(*func)())
{

	for (auto p : functionallitys)
	{
		if (p.first == id) return false;

	}

	functionallitys.push_back({ id,func });
	return true;
}

