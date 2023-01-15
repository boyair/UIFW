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

		//Send error message if window creation Failed.
		if (!window.Hwnd)
		{
			MessageBox(NULL, (wstring(L"Failed to ctreate window \"") + window.text + wstring(L"\"please check your code")).c_str(), L"Failure!", MB_ICONERROR | MB_OK);
			return;
		}

		//message loop
		MSG msg;
		while (GetMessage(&msg, window.Hwnd, NULL, NULL) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}


	}

	ExtraWindow::ExtraWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B) :MainWindow(Text, x, y, width, height), winmade(CreateEvent(NULL, FALSE, FALSE, NULL))
	{
#if _DEBUG
		if (winmade == NULL)
		{
			DWORD error = GetLastError();
			MessageBox(NULL, L"event creation failed!!", L"error", MB_OK | MB_ICONERROR);
			return;
		}
#endif
		CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));

		style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

		procthread = std::thread(HandleOnThread, std::ref(*this));
		//waits until the window was created so that menus and childwindow can be created on it later. 

		WaitForSingleObject(winmade, INFINITE);


	}
	ExtraWindow::~ExtraWindow()
	{
		procthread.join();
	}



};