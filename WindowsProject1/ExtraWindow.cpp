#include "ExtraWindow.h"
namespace UIFW {
	void HandleOnThread(ExtraWindow& window)
	{
		window.CLS.lpszClassName = window.text.c_str();
		RegisterClassW(&window.CLS);
		// Create the window
		window.Hwnd = CreateWindowW(window.CLS.lpszClassName, window.text.c_str(), window.style, window.x, window.y, window.width, window.height, NULL, NULL, NULL, NULL);
		SetEvent(window.winmade);	//allows main thread to continue
		SetWindowLongPtr(window.Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&window));
#if _DEBUG
		//Send error message if window creation Failed.
		if (!window.Hwnd)
		{
			MessageBox(NULL, (wstring(L"Failed to ctreate window \"") + window.text + wstring(L"\"please check your code")).c_str(), L"Failure!", MB_ICONERROR | MB_OK);
			return;
		}
#endif
		//message loop
		MSG msg;
		while (GetMessage(&msg, window.Hwnd, NULL, NULL) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}


	}

	ExtraWindow::ExtraWindow():MainWindow(), winmade(CreateEvent(NULL, FALSE, FALSE, NULL))
	{
	}

	ExtraWindow::ExtraWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B) :MainWindow(Text, x, y, width, height), winmade(CreateEvent(NULL, FALSE, FALSE, NULL))
	{
		if (winmade == NULL)
		{
			DWORD error = GetLastError();
			MessageBox(NULL, L"event creation failed!!", L"error", MB_OK | MB_ICONERROR);
			return;
		}

		CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));

		style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

		procthread = std::thread(HandleOnThread, std::ref(*this));
		//waits until the window was created so that menus and childwindow can be created on it later. 

		WaitForSingleObject(winmade, INFINITE);


	}
	void ExtraWindow::Init(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned char G, unsigned char B)
	{

		this->text = Text;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		CLS.lpszClassName = text.c_str();

		if (winmade == NULL)
		{
			DWORD error = GetLastError();
			MessageBox(NULL, L"event creation failed!!", L"error", MB_OK | MB_ICONERROR);
			return;
		}

		CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));

		style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

		procthread = std::thread(HandleOnThread, std::ref(*this));
		//waits until the window was created so that menus and childwindow can be created on it later. 

		WaitForSingleObject(winmade, INFINITE);
	}ExtraWindow::ExtraWindow(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B) :MainWindow(std::move(Text), x, y, width, height), winmade(CreateEvent(NULL, FALSE, FALSE, NULL))
	{
		if (winmade == NULL)
		{
			DWORD error = GetLastError();
			MessageBox(NULL, L"event creation failed!!", L"error", MB_OK | MB_ICONERROR);
			return;
		}

		CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));

		style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

		procthread = std::thread(HandleOnThread, std::ref(*this));
		//waits until the window was created so that menus and childwindow can be created on it later. 

		WaitForSingleObject(winmade, INFINITE);

		
	}
	ExtraWindow::ExtraWindow(wstring&& Text, int x, int y, int width, int height, const image& img):MainWindow(std::move(Text), x, y, width, height), winmade(CreateEvent(NULL, FALSE, FALSE, NULL))
	{
		if (winmade == NULL)
		{
			DWORD error = GetLastError();
			MessageBox(NULL, L"event creation failed!!", L"error", MB_OK | MB_ICONERROR);
			return;
		}
		this->img = img;
		HBRUSH hBrush = CreatePatternBrush(img.BM);
		//SetWindowLongPtr(Hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
		CLS.hbrBackground = hBrush;
		//make window unresizeable
		style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE | WS_CLIPCHILDREN;
		procthread = std::thread(HandleOnThread, std::ref(*this));
		//waits until the window was created so that menus and childwindow can be created on it later. 

		WaitForSingleObject(winmade, INFINITE);
		SendMessage(Hwnd, WM_ERASEBKGND, (WPARAM)GetDC(Hwnd), 0);
	}
	ExtraWindow::ExtraWindow(const wstring& Text, int x, int y, int width, int height, const image& img) :MainWindow(Text, x, y, width, height), winmade(CreateEvent(NULL, FALSE, FALSE, NULL))
	{
		if (winmade == NULL)
		{
			DWORD error = GetLastError();
			MessageBox(NULL, L"event creation failed!!", L"error", MB_OK | MB_ICONERROR);
			return;
		}
		this->img = img;
		HBRUSH hBrush = CreatePatternBrush(img.BM);
		//SetWindowLongPtr(Hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
		CLS.hbrBackground = hBrush;
		//make window unresizeable
		style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE| WS_CLIPCHILDREN;
		procthread = std::thread(HandleOnThread, std::ref(*this));
		//waits until the window was created so that menus and childwindow can be created on it later. 

		WaitForSingleObject(winmade, INFINITE);
		SendMessage(Hwnd, WM_ERASEBKGND, (WPARAM)GetDC(Hwnd), 0);
	}
	void ExtraWindow::Init(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned char G, unsigned char B)
	{
		this->text = std::move(Text);
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		CLS.lpszClassName = text.c_str();

		if (winmade == NULL)
		{
			DWORD error = GetLastError();
			MessageBox(NULL, L"event creation failed!!", L"error", MB_OK | MB_ICONERROR);
			return;
		}

		CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));

		style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

		procthread = std::thread(HandleOnThread, std::ref(*this));
		//waits until the window was created so that menus and childwindow can be created on it later. 

		WaitForSingleObject(winmade, INFINITE);
	}
	void ExtraWindow::Destroy()
	{
		if (Hwnd)
		{
			PostMessage(Hwnd, WM_CLOSE, 1, 0);
			procthread.join();
		}
	}
	ExtraWindow::~ExtraWindow()
	{
		if (Hwnd)
		{
			PostMessage(Hwnd, WM_CLOSE, 1, 0);
		}
			if(procthread.joinable())
				procthread.join();
	}



};