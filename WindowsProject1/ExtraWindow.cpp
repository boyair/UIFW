#include "ExtraWindow.h"

void HandleOnThread(ExtraWindow& window)
{

	window.CLS.lpszClassName = window.text.c_str();
	RegisterClassW(&window.CLS);
	
	// Create the window
	window.Hwnd = CreateWindowW(window.CLS.lpszClassName, window.text.c_str(), window.style, window.x, window.y, window.width, window.height, NULL, NULL, NULL, NULL);
	
	SetWindowLongPtr(window.Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&window));
	
	//Send error message if window creation Failed.
	if (!window.Hwnd)
	{
		MessageBox(NULL,(wstring( L"Failed to ctreate window \"") + window.text + wstring(L"\"please check your code")).c_str(), L"Failure!" , MB_ICONERROR | MB_OK);
		return;
	}

	//message loop
	RECT rct;
	GetWindowRect(window.Hwnd, &rct);
	RedrawWindow(window.Hwnd, &rct, NULL, RDW_ERASE);
	MSG msg;
	while (GetMessage(&msg, window.Hwnd, NULL, NULL)>0)
	{	
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}


}
extern LRESULT CALLBACK NonStaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

ExtraWindow::ExtraWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B) :MainWindow(Text, x, y, width, height)
{
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	
	procthread = std::thread(HandleOnThread,std::ref(*this));
	
	
}
ExtraWindow::~ExtraWindow()
{
	procthread.join();
}



