#include "MainWindow.h"
#include "ChildWindow.h"

namespace UIFW {
	LRESULT MainWindow::Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{

		case WM_USER + 1:
		{
			//handles manipulation of ChildWindows on thread
			ChildWindow* pl = (ChildWindow*)lp;
			switch (wp)
			{
			case 1:
				((ChildWindow*)lp)->place();
				SetEvent(((ChildWindow*)lp)->winmade);
				break;

			case 2:
				DestroyWindow(((ChildWindow*)lp)->Hwnd);
				SetEvent(((ChildWindow*)lp)->winmade);
				break;

			case 3:
				((ChildWindow*)lp)->SendImage();
				break;

			}
			//SetEvent(((ChildWindow*)lp)->winmade);
			break;
		}



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
			HBRUSH BK = CreateSolidBrush(RGB(EditWindowColorBK[0], EditWindowColorBK[1], EditWindowColorBK[2]));
			HDC hdcStatic = (HDC)wp;
			SetTextColor(hdcStatic, RGB(EditWindowColorText[0], EditWindowColorText[1], EditWindowColorText[2]));
			SetBkColor(hdcStatic, RGB(EditWindowColorBK[0], EditWindowColorBK[1], EditWindowColorBK[2]));
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
			if (onexit)
				onexit();
			PostQuitMessage(0);
			break;
		}
		return DefWindowProcW(hwnd, msg, wp, lp);

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

	MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height, const image& img) :MainWindow(Text, x, y, width, height)
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
		if (ChildMenus.size() < menuindex) return false;

		//add sub menu
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

	bool MainWindow::AddFunc(int id, std::function<void()> func)
	{
		//test if id exists already
		for (auto p : functionallitys)
		{
			if (p.first == id) return false;

		}
		//adds functionallity
		functionallitys.push_back({ id,func });
		return true;
	}


	
}
