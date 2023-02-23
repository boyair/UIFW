#include "MainWindow.h"
#include "ChildWindow.h"

namespace UIFW {
	LRESULT MainWindow::Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		if (OnUpdate)OnUpdate();
		switch (msg)
		{
		case WM_USER + 1:
		{
			//handles manipulation of ChildWindows on thread
			ChildWindow* pl = (ChildWindow*)lp;
			
			if (wp)
			{
				((ChildWindow*)lp)->place();
				SetEvent(((ChildWindow*)lp)->winmade);
			}
			else
			{
				DestroyWindow(((ChildWindow*)lp)->Hwnd);
				SetEvent(((ChildWindow*)lp)->winmade);
			}
			break;
		}



		case WM_ERASEBKGND:


			if (&img && img.BM)
			{
				HDC hdc = (HDC)wp;
				RECT rect;
				GetClientRect(hwnd, &rect);
				// Create a memory device context for the image
				HDC hdcMem = CreateCompatibleDC(hdc);
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, img.BM);
				// Stretch the image to fit the window
				SetStretchBltMode(hdc, HALFTONE);
				StretchBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, img.width, img.height, SRCCOPY);
				// Clean up
				SelectObject(hdcMem, hOldBitmap); // Deselect the bitmap handle from the memory device context
				DeleteDC(hdcMem);
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
			HBRUSH BK = CreateSolidBrush(RGB(EditWindowColorBK[0], EditWindowColorBK[1], EditWindowColorBK[2]));
			HDC hdcStatic = (HDC)wp;
			SetTextColor(hdcStatic, RGB(EditWindowColorText[0], EditWindowColorText[1], EditWindowColorText[2]));
			SetBkColor(hdcStatic, RGB(EditWindowColorBK[0], EditWindowColorBK[1], EditWindowColorBK[2]));
			return (INT_PTR)BK;
		}
		case WM_COMMAND:
			if (functionallitys.find((int)wp) != functionallitys.end())
				functionallitys[(int)wp]();
			break;

		case WM_CLOSE:
			if (XButton&&!wp)
			{
				XButton();
				return 0;
			}
			DestroyWindow(Hwnd);
			Hwnd = nullptr;

			break;



		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		
		return DefWindowProcW(hwnd, msg, wp, lp);

	}
	void MainWindow::UpdateRECT()
	{
		RECT newrect;
		GetWindowRect(Hwnd,  & newrect);
		x = newrect.left;
		y = newrect.top;
		width = newrect.right - x;
		height = newrect.bottom - y;
		
	}
	static LRESULT CALLBACK NonStaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{

		MainWindow* window = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (window)
		
			return window->Proc(hwnd, uMsg, wParam, lParam);
		
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}




	MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height) :Window(Text, x, y, width, height)
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

	MainWindow::MainWindow() :Window()
	{
		CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
		CLS.hInstance = GetModuleHandle(NULL);
		CLS.lpfnWndProc = NonStaticWindowProc;
		functionallitys.reserve(4);
	}

	MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height, const image& img) :MainWindow(Text, x, y, width, height)
	{
		//sets background image
		this->img = img;
		CLS.hbrBackground = HBRUSH(COLOR_DESKTOP);
		//make window unresizeable
		style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WS_CLIPCHILDREN;
		RegisterClassW(&CLS);
		//create window
		Hwnd = CreateWindow(text.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
		SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		SendMessage(Hwnd, WM_ERASEBKGND, (WPARAM)GetDC(Hwnd), 0);

	}

	MainWindow::MainWindow(wstring&& Text, int x, int y, int width, int height, const image& img) :MainWindow(std::move(Text), x, y, width, height)
	{
		//sets background image
		this->img = img;
		CLS.hbrBackground = HBRUSH(COLOR_DESKTOP);
		//make window unresizeable
		style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WS_CLIPCHILDREN;
		RegisterClassW(&CLS);
		//create window
		Hwnd = CreateWindow(text.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
		SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		SendMessage(Hwnd, WM_ERASEBKGND, (WPARAM)GetDC(Hwnd), 0);
	}


	MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B) :MainWindow(Text, x, y, width, height)
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

	void MainWindow::Init(const wstring& Text, int x, int y, int width, int height, const image& img)
	{
		
		this->text = Text;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		CLS.lpszClassName = text.c_str();

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

	void MainWindow::Init(wstring&& Text, int x, int y, int width, int height, const image& img)
	{
		
		this->text = std::move(Text);
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		CLS.lpszClassName = text.c_str();
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

	void MainWindow::Init(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B) 
	{
		
		this->text = Text;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		CLS.lpszClassName = text.c_str();
		//sets background image
		CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
		//make window resizeable
		style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		RegisterClassW(&CLS);
		//create window
		Hwnd = CreateWindow(text.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
		SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	}

	void MainWindow::Init(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B)
	{
		
		this->text = std::move(Text);
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		CLS.lpszClassName = text.c_str();
		//sets background image
		CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
		//make window resizeable
		style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		RegisterClassW(&CLS);
		//create window
		Hwnd = CreateWindow(text.c_str(), text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
		SetWindowLongPtr(Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}


	POINT MainWindow::GetMousePos()
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(Hwnd, &p);

		return p;
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

	void MainWindow::SetColor_EditWindow_Text(unsigned char R, unsigned  char G, unsigned  char B)
	{
		EditWindowColorText[0] = R;
		EditWindowColorText[1] = G;
		EditWindowColorText[2] = B;
	}

	void MainWindow::SetColor_EditWindow_BK(unsigned char R, unsigned  char G, unsigned  char B)
	{
		EditWindowColorBK[0] = R;
		EditWindowColorBK[1] = G;
		EditWindowColorBK[2] = B;
	}

	void MainWindow::AddMenu(const wstring& name, long id, bool parent)
	{
		//adds parent menu
		if (parent)
		{
			ChildMenus.push_back(CreateMenu());
			AppendMenuW(menu, MF_POPUP, (UINT_PTR)ChildMenus.back(), name.c_str());
		}
		//adds regular menu
		else
			AppendMenuW(menu, MF_STRING, id, name.c_str());
		SetMenu(Hwnd, menu);
	}

	bool MainWindow::AddSubMenu(const wstring& name, int menuindex, long id)
	{
		//check if addition is not possible
		if ((int)ChildMenus.size() < menuindex) return false;

		//add sub menu
		AppendMenu(ChildMenus[menuindex], MF_STRING, id, name.c_str());
		return true;
	}

	void MainWindow::RemoveMenuBar()
	{
		SetMenu(Hwnd, NULL);

	}


	void MainWindow::Start()
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
		if (Hwnd)
		PostMessage(Hwnd, WM_CLOSE, 1, 0);

	}

	RECT MainWindow::GetRECT()
	{
		UpdateRECT();
		return Window::GetRECT();
	}

	void MainWindow::Move(int DX, int DY)
	{
		UpdateRECT();
		Window::Move(DX, DY);
		

	}

	void MainWindow::Resize(int width, int height)
	{
		UpdateRECT();
		Window::Resize(width, height);
		if(&img && img.BM)
			SendMessage(Hwnd, WM_ERASEBKGND, (WPARAM)GetDC(Hwnd), 0);

	}

	void MainWindow::Reposition(int x, int y)
	{
		UpdateRECT();
		Window::Reposition(x, y);
	}

}
