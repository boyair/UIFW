#include "MainWindow.h"

std::vector<std::pair<int, void(*)()>> functionallitys;


LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{

	switch (msg)
	{
	case WM_COMMAND:


		
		
		for (auto&[num,func] : functionallitys)
		{
			if (num == wp)
			{
				func();
				break;
			}
				
			
		}


		//switch (wp)
		//{
		//case 1:
		//	MessageBeep(MB_OK);
		//	break;
		//case 2:
		//	MessageBox(hwnd, L" you sure???", L"L", MB_YESNO);
		//	break;
		//case 3:
		//
		//	break;
		//case 4:
		//	break;
		//
		//case 5:
		//
		//
		//
		//
		//
		//
		//	break;
		//
		//}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hwnd, msg, wp, lp);
	}
	return DefWindowProcW(hwnd, msg, wp, lp);

}



MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height):Window(Text, x, y, width, height)
{
	
	 CLS.hbrBackground = HBRUSH(COLOR_DESKTOP);
	 CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	 CLS.hInstance = GetModuleHandle(NULL);
	 CLS.lpszClassName = L"WNDCLS";
	 CLS.lpfnWndProc = Proc;
	 functionallitys.reserve(4);
	RegisterClassW(&CLS);
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	Hwnd = CreateWindow(L"WNDCLS", Text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	

}

MainWindow::MainWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B):Window(Text, x, y, width, height)
{
	CLS.hbrBackground = CreateSolidBrush(RGB(R, G, B));
	CLS.hCursor = LoadCursor(NULL, IDC_ARROW);
	CLS.hInstance = GetModuleHandle(NULL);
	CLS.lpszClassName = L"WNDCLS";
	CLS.lpfnWndProc = Proc;
	functionallitys.reserve(4);
	RegisterClassW(&CLS);
	style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	Hwnd = CreateWindow(L"WNDCLS", Text.c_str(), style, x, y, width, height, NULL, NULL, NULL, NULL);
	


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

bool MainWindow::AddFunc(int id, void(*func)())
{
	for (auto p : functionallitys)
	{
		if (p.first == id) return false;

	}

	functionallitys.push_back({ id,func });
	return true;
}

