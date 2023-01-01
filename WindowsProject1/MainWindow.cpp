#include "MainWindow.h"
//should change this to unordered_map


HDC hdcStatic;
LRESULT MainWindow::Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{

	//case WM_CTLCOLORSTATIC:
	//	
	//		SetBkMode(HDC(wp), TRANSPARENT);
	//		return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
	//
	//		break;

	 


	case WM_CTLCOLOREDIT:

		SetBkMode(HDC(wp), TRANSPARENT);
		return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);

		break;
		
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
	LONG_PTR save = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	MainWindow* window = reinterpret_cast<MainWindow*>(save);
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
	
	//// CLS.hbrBackground = HBRUSH(COLOR_DESKTOP);
	// CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	// CLS.hInstance = GetModuleHandle(NULL);
	// CLS.lpfnWndProc = NonStaticWindowProc;
	// functionallitys.reserve(4);
	//style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	// CLS.lpszClassName = L"WNDCLS";
	 
	//RegisterClassW(&CLS);
	//Hwnd = CreateWindow(L"WNDCLS", Text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	//SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));


}



MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B, wstring classname):MainWindow(Text, x, y, width, height)
{
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpszClassName = classname.c_str();
	//CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpfnWndProc = NonStaticWindowProc;
	functionallitys.reserve(4);
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	//CLS.lpszClassName = classname.c_str();
	//CLS.lpfnWndProc = NonStaticWindowProc;
	//functionallitys.reserve(4);
	RegisterClassW(&CLS);
	//style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	Hwnd = CreateWindow(classname.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	save = GetWindowLongPtr(Hwnd, GWLP_USERDATA);


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

	
	

	//SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	//save = GetWindowLongPtr(Hwnd, GWLP_USERDATA);


	
	while (GetMessage(&msg, Hwnd, NULL, NULL) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void MainWindow::Destroy()
{
	PostMessage(Hwnd, WM_DESTROY, 0, 0);
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

