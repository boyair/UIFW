#include "ExtraWindow.h"

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

	//message loop
	MSG msg;
	while (GetMessage(&msg, window.Hwnd, NULL, NULL)>0)
	{	
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}


}
extern LRESULT CALLBACK NonStaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

ExtraWindow::ExtraWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B) :MainWindow(Text, x, y, width, height)
{
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	
	procthread = std::thread(HandleOnThread,std::ref(*this));
	
	
}



ExtraWindow::~ExtraWindow()
{
	procthread.join();
}



