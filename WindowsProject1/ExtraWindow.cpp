#include "ExtraWindow.h"
#include "button.h"
//extern ExtraWindow win2;
//ExtraWindow* Procede;
LRESULT CALLBACK NonStaticWindowProcThread(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



	//Button Typer2(1);
void HandleOnThread(ExtraWindow& window)
{

	RegisterClassW(&window.CLS);
	
	// Create the window
	window.Hwnd = CreateWindowW(window.CLS.lpszClassName, window.text.c_str(), WS_OVERLAPPED | 
		WS_CAPTION | 
		WS_SYSMENU | 
		WS_THICKFRAME | WS_VISIBLE, window.x, window.y, window.width, window.height, NULL, NULL, NULL, NULL);
	//DWORD THISTHREAD = GetCurrentThreadId();
	//AttachThreadInput(		window.MainID,THISTHREAD,	true	);
	
	if (!window.Hwnd)
	{
		MessageBox(NULL,(wstring( L"Failed to ctreate window \"") + window.text + wstring(L"\"please check your code")).c_str(), L"Failure!" , MB_ICONERROR | MB_OK);
		return;
	}
	
	//set correct proc function for "NonStaticWindowProcThread".
	SetWindowLongPtr(window.Hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&window));


	//message loop
	MSG msg;
	while (GetMessage(&msg, window.Hwnd, NULL, NULL)>0)
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




void ExtraWindow::ReciveWindowAndHandle()
{
	if ( ToHandle&&ChildFunc)
	{
		switch (ChildFunc)
		{
		case 1:
			ToHandle->place();
			ToHandle = nullptr;
			ChildFunc = 0;
			break;
		case 2:
			DestroyWindow(ToHandle->Hwnd);
			ToHandle = 0;
			ChildFunc = 0;
			break;
		case 3:

			ToHandle->SetText(ToHandle->text);
			ToHandle = nullptr;
			ChildFunc = 0;
			break;
		case 4:
			SendMessageW(ToHandle->Hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)ToHandle->img->BM);
			ToHandle = nullptr;
			ChildFunc = 0;

			break;


		}
	}

}

LRESULT ExtraWindow::Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_USER +1:

		
		switch (wp)
		{
		case 1:
			((ChildWindow*)lp)->place();
			//((ChildWindow*)lp) = nullptr;
			
			break;
		case 2:
			DestroyWindow(((ChildWindow*)lp)->Hwnd);
			//((ChildWindow*)lp) = 0;
			
			break;
		case 3:

			((ChildWindow*)lp)->SetText(((ChildWindow*)lp)->text);
			//((ChildWindow*)lp) = nullptr;
			
			break;
		case 4:
			//SendMessageW(((ChildWindow*)lp)->Hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)(((ChildWindow*)lp)->img->BM));
			((ChildWindow*)lp)->addimage(*((ChildWindow*)lp)->img);

			break;
		}


		break;

	case WM_CTLCOLORSTATIC:

		SetBkMode(HDC(wp), TRANSPARENT);
		return (INT_PTR)(HBRUSH)GetStockObject(NULL_BRUSH);

		break;


	
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
	
	procthread = std::thread(HandleOnThread,std::ref(*this));
	
	
}

void ExtraWindow::start()
{
	started = true;
}

ExtraWindow::~ExtraWindow()
{
	procthread.join();
}



