#include <sstream>
#include "Menu.h"
#include "TextBox.h"
#include "Button.h"
HWND Hwindow;
LRESULT CALLBACK  winproc(HWND, UINT, WPARAM, LPARAM);
void addmenu(HWND&);
 TextBox edit(true);
 Button move(1);
void addcontrols(HWND& hwnd);
std::pair<int, int> getsize(HWND& hwnd);
HWND Hedit;

int WINAPI WinMain(HINSTANCE Hinst, HINSTANCE hprevinst, LPSTR args, int ncmdshow)
{
	//creating empty window
	WNDCLASSW window = { 0 };
	window.hbrBackground = (HBRUSH)2;
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hInstance = Hinst;
	window.lpszClassName = L"my window class";
	window.lpfnWndProc = winproc;
	RegisterClassW(&window);
	 Hwindow = CreateWindowW(L"my window class", L"title",  WS_OVERLAPPEDWINDOW, 2000, 10, 500, 500, NULL, NULL, NULL,NULL);
	//adding things needed at start
	  edit.set(L"12345678901234567890", 190, 70, 70, 70, &Hwindow);
	  move.set(L"Move", 70, 70, 100, 30,3, &Hwindow);
	  edit.AddHorizontalScrolling();
	  edit.AddVerticalScrolling();
	  

	addcontrols(Hwindow);
	addmenu(Hwindow);




	//massage loop
	MSG msg;
	while (GetMessage(&msg,NULL,NULL,NULL)>0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}

LRESULT CALLBACK  winproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	std::wstring arr;
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
			
			edit.AddBorder();
			edit.SetText(L"Hello world momomoi");

			break;
		case 4:
			 arr =
				edit.GetText();
			SetWindowTextW(hwnd, arr.c_str());
			break;
		case 5:


			int x, y;
			std::pair<int, int> size = getsize(hwnd);
			std::wstringstream ss;
			ss << edit.GetText();
			ss >> x >> y;
			if (size.first > x&& size.first > 0-x && size.second > y && size.second > 0 - y)
			edit.Move(x, y);
			move.AddBorder();
			
			break;
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hwnd, msg, wp, lp);
	}

}
void addmenu(HWND& parent)
{


	Menu file(&parent, "file", 1,true);
	Menu quit(&parent, "quit", 2, false);
	file.AddSubMenu("new",2);
	quit.AddSubMenu("yes", 3);
	quit.AddSubMenu("no", 0);
	file.AddSubMenu("change title", 4);


}

void addcontrols(HWND& hwnd)
{

	//CreateWindowW(L"static", L"text brinded", WS_VISIBLE | WS_CHILD|WS_BORDER|SS_CENTER, 70, 70, 100, 30, hwnd, NULL, NULL, NULL);
	//CreateWindowW(L"button", L"move", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 70, 70, 100, 30, hwnd, (HMENU) 5, NULL, NULL);

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

