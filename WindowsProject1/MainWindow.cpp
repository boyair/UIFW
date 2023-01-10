#include "MainWindow.h"
#include "ChildWindow.h"


LRESULT MainWindow::Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{

	case WM_USER + 1:

		//handles manipulation of ChildWindows on thread
		if (wp) {
			((ChildWindow*)lp)->place();
			break;
		}

		DestroyWindow(((ChildWindow*)lp)->Hwnd);
		break;




	case WM_ERASEBKGND:
	
	
		if (&img && img.BM)
		{
			
			HDC hdc = (HDC)wp;
			RECT rect;
			GetClientRect(hwnd, &rect);
	
	
			img.BM = (HBITMAP)LoadImageW(NULL, img.name.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
			// Create a memory device context for the image
			HDC hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, img.BM);
	
			// Stretch the image to fit the window
			SetStretchBltMode(hdc, HALFTONE);
			StretchBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, img.width, img.height, SRCCOPY);
	
			// Clean up
			DeleteDC(hdcMem);
			DeleteObject(img.BM);
	
	
			return 1;
		}
	
		break;

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
		if(onexit)
			onexit();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, msg, wp, lp);

}
LRESULT CALLBACK NonStaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	MainWindow* window = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (window)
	
		return window->Proc(hwnd, uMsg, wParam, lParam);
	
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}




MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height):Window(Text, x, y, width, height)
{
	 //sets up WNDCLS except for background
	 CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	 CLS.hInstance = GetModuleHandle(NULL);
	 CLS.lpfnWndProc = NonStaticWindowProc;
	 CLS.lpszClassName = Text.c_str();

	 functionallitys.reserve(4);
}

MainWindow::MainWindow(wstring&& Text, int x, int y, int width, int height) :Window(std::move(Text), x, y, width, height)
{
	//sets up WNDCLS except for background
	CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpfnWndProc = NonStaticWindowProc;
	CLS.lpszClassName = text.c_str();

	functionallitys.reserve(4);
}

MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height, const image& img):MainWindow(Text,x,y,width,height)
{
	//sets background image
	this->img = img;
	CLS.hbrBackground = HBRUSH(COLOR_DESKTOP);
	//make window unresizeable
	style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	RegisterClassW(&CLS);
	//create window
	Hwnd = CreateWindow(Text.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

MainWindow::MainWindow(wstring&& Text, int x, int y, int width, int height, const image& img) :MainWindow(std::move(Text), x, y, width, height)
{
	//sets background image
	this->img = img;
	CLS.hbrBackground = HBRUSH(COLOR_DESKTOP);
	//make window unresizeable
	style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE;
	RegisterClassW(&CLS);
	//create window
	Hwnd = CreateWindow(text.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}


MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B):MainWindow(Text, x, y, width, height)
{
	//sets background image
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	//make window resizeable
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	RegisterClassW(&CLS);
	//create window
	Hwnd = CreateWindow(text.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	
}

MainWindow::MainWindow(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B) :MainWindow(std::move(Text), x, y, width, height)
{
	//sets background image
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	//make window resizeable
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	RegisterClassW(&CLS);
	//create window
	Hwnd = CreateWindow(text.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

}

void MainWindow::SetColor_Child_Text(unsigned char R, unsigned  char G, unsigned  char B)
{
	ChildColorText[0] = R;
	ChildColorText[1] = G;
	ChildColorText[2] = B;

}

void MainWindow::SetColor_Child_BK(unsigned char R, unsigned  char G, unsigned  char B)
{
	
	ChildColorBK[0] = R;
	ChildColorBK[1] = G;
	ChildColorBK[2] = B;
}

void MainWindow::SetColor_EW_Text(unsigned char R, unsigned  char G, unsigned  char B)
{
	EWColorText[0] = R;
	EWColorText[1] = G;
	EWColorText[2] = B;
}

void MainWindow::SetColor_EW_BK(unsigned char R, unsigned  char G, unsigned  char B)
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

