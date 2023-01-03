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




		//case WM_CTLCOLOREDIT:
		//
		//	SetBkMode(HDC(wp), TRANSPARENT);
		//	return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);
		//
		//	break;
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
	
		return window->Proc(hwnd, uMsg, wParam, lParam);
	
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
	


}

void MainWindow::SetColor_Child_Text(char R, char G, char B)
{
	ChildColorText[0] = R;
	ChildColorText[1] = G;
	ChildColorText[2] = B;

}

void MainWindow::SetColor_Child_BK(char R, char G, char B)
{
	
	ChildColorBK[0] = R;
	ChildColorBK[1] = G;
	ChildColorBK[2] = B;
}

void MainWindow::SetColor_EW_Text(char R, char G, char B)
{
	EWColorText[0] = R;
	EWColorText[1] = G;
	EWColorText[2] = B;
}

void MainWindow::SetColor_EW_BK(char R, char G, char B)
{
	EWColorBK[0] = R;
	EWColorBK[1] = G;
	EWColorBK[2] = B;
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
	SetMenu(Hwnd, menu);
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

	MSG msg;
	
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

