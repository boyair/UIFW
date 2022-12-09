#include <sstream>
#include "Menu.h"
#include "EW.h"
#include "Button.h"
#include "image.h"
HWND Hwindow;
LRESULT CALLBACK  winproc(HWND, UINT, WPARAM, LPARAM);
			image img;
void addmenu(HWND&);
 EW edit;
 ChildWindow tester;
 Button move(5);
void addcontrols(HWND& hwnd);

std::pair<int, int> getsize(HWND& hwnd);
HWND Hedit;

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
	//creating empty window
	WNDCLASSW window = { 0 };
	window.hbrBackground = (HBRUSH)COLOR_DESKTOP;
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hInstance = hInstance;
	window.lpszClassName = L"my window class";
	window.lpfnWndProc = winproc;
	RegisterClassW(&window);
	 Hwindow = CreateWindowW(L"my window class", L"title",  WS_OVERLAPPEDWINDOW| WS_VISIBLE, 2000, 10, 1000, 1000, NULL, NULL, NULL,NULL);
	//adding things needed at start
	 
	  addcontrols(Hwindow);
	  addmenu(Hwindow);




	//massage loop
	MSG msg;
	while (GetMessage(&msg,Hwindow,NULL,NULL)>0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}

wstring arr;
LRESULT CALLBACK  winproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	
	switch (msg)
	{
	case WM_COMMAND:

		switch (wp)
		{
		case 1:
			MessageBeep(MB_OK);
			break;
		case 2:
			 MessageBox(hwnd,L" you sure???",L"L",MB_YESNO);
			break;
		case 3:
			
			break;
		case 4:
			break;

		case 5:
			if(img.LoadFromFile(L"tank.bmp"))
			move.addimage(img);

			
			
			
			
			break;
		
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hwnd, msg, wp, lp);
	}
	return DefWindowProcW(hwnd, msg, wp, lp);

}
void addmenu(HWND& parent)
{


	Menu file(&parent, L"file", 1,true);
	Menu quit(&parent, L"quit", 2, false);
	file.destroy();
	file.AddSubMenu(L"new",2);
	quit.AddSubMenu(L"yes", 3);
	quit.AddSubMenu(L"no", 0);
	file.AddSubMenu(L"change title", 4);


}

void addcontrols(HWND& hwnd)
{
	edit.set(L"12345678901234567890", 190, 90, 70, 70, &hwnd);
	move.set(L"Move", 70, 70, 100, 30, &hwnd);
	tester.set(L"Hello", 300, 300, 80, 80, &hwnd);
	image img;
	img.LoadFromFile(L"tank.bmp",70,70);
	ChildWindow stat(0, 500, 500, 70, 70, &hwnd);
	stat.AddBorder();
	stat.addimage(img);
}


std::pair<int, int> getsize(HWND& hwnd)
{
	int width, height;
	RECT wnd;
	GetWindowRect(hwnd, &wnd);
	width = wnd.right - wnd.left;
	height = wnd.bottom - wnd.top;

	return {width, height};

}

//tasks:
 
//make a main window class

// add more comments in functions.

//optimizations

//debug only safe guards

//manage messageboxas

//try add sound