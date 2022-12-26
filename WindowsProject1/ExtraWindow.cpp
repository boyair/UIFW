#include "ExtraWindow.h"
#include "button.h"
//extern ExtraWindow win2;
std::vector<ExtraWindow*> Procede;
//ExtraWindow* Procede;
LRESULT CALLBACK NonStaticWindowProcThread(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



	Button Typer2(1);
void CreateWindow1(ExtraWindow& window)
{

	RegisterClassW(&window.CLS);
	
	// Create the window
	window.Hwnd = CreateWindowW(window.CLS.lpszClassName, window.text.c_str(), WS_OVERLAPPED | 
		WS_CAPTION | 
		WS_SYSMENU | 
		WS_THICKFRAME | WS_VISIBLE, window.x, window.y, window.width, window.height, NULL, NULL, NULL, NULL);
	if (!window.Hwnd)
	{
		MessageBox(NULL,(wstring( L"Failed to ctreate window \"") + window.text + wstring(L"\"please check your code")).c_str(), L"Failure!" , MB_ICONERROR | MB_OK);
		return;
	}
	
	// Show the window
	ShowWindow(window.Hwnd, SW_SHOW);
	Typer2.set(L"asdasda", 230, 190, 90, 90, &window);
	//hang till the client starts the window
	while (!window.started);

	
	Procede .push_back(& window);
	SetWindowLongPtr(window.Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&window));
	MSG msg;
	while (GetMessage(&msg, window.Hwnd, NULL, NULL) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}


LRESULT CALLBACK NonStaticWindowProcThread(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	

	ExtraWindow* window = reinterpret_cast<ExtraWindow*>( GetWindowLongPtr(hwnd, GWLP_USERDATA));
	
	
	if (window)
	{
		return window->Proc(window->Hwnd, uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
void threadhang(ExtraWindow* window, const wstring& Text, int x, int y, int width, int height, int R, int G, int B, wstring classname)
{
	// Procede = window;
	
	window->Hwnd = CreateWindow(classname.c_str(), Text.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, width, height, NULL, NULL, NULL, NULL);
	while (!window->started)
	{

	}
	MSG msg;
	while (GetMessage(&msg, window->Hwnd, NULL, NULL) > 0 )
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

ExtraWindow::ExtraWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B, wstring classname) :MainWindow(Text, x, y, width, height)
{
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpszClassName = text.c_str();
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpfnWndProc = NonStaticWindowProcThread;
	functionallitys.reserve(4);
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	
	procthread = std::thread(CreateWindow1,std::ref(*this));
	
	
}

void ExtraWindow::start()
{
	started = true;
}

ExtraWindow::~ExtraWindow()
{
	procthread.join();
}



