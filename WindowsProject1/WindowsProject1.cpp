#include <sstream>
#include "Menu.h"
#include "EW.h"
#include "Button.h"
#include "image.h"
#include "MainWindow.h"
HWND Hwindow;


//LRESULT CALLBACK  winproc(HWND, UINT, WPARAM, LPARAM);
			image img;
//void addmenu(MainWindow&);
 EW edit;
 Button nums[9] = {(1),(2),(3),(4),(5),(6),(7),(8),(9)};
 ChildWindow tester;
 int i;
 Button move(5);
 Button Typer(1);
void addcontrols(MainWindow& hwnd);

std::pair<int, int> getsize(HWND& hwnd);
HWND Hedit;

//int main()
//{
//	MainWindow Main(R,G,B,x,y,width,height)
//
//
//
//}


void (*create_function())(void)
{
	
	auto thefunc = []()
	{
		wchar_t num[8];
			swprintf_s(num,8,L"%d",i);
			wstring newtext = edit.GetText();
			newtext += num;
			edit.SetText(newtext);


	};
	return thefunc;

}



int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
	//creating empty window
	//WNDCLASSW window{ 0};
	//window.hbrBackground = CreateSolidBrush(RGB(90,90,9));
	//window.hCursor = LoadCursor(NULL, IDC_ARROW);
	//window.hInstance = hInstance;
	//window.lpszClassName = L"my window class";
	//window.lpfnWndProc = winproc;
	//RegisterClassW(&window);
	// Hwindow = CreateWindowW(L"my window class", L"title",  WS_OVERLAPPEDWINDOW| WS_VISIBLE, 2000, 10, 1000, 1000, NULL, NULL, NULL,NULL);
	
	  //ChildWindow stat(L"Hello", 7, 7, 80, 80, &win);
	MainWindow win(L"W working window", 2000, 20, 1000, 1000, 255, 0, 0);
	//ChildWindow sta;
	//sta.set(L"Hello", 7, 7, 80, 80, &win);
	for (size_t i = 0; i < 9; i++)
	{
		std::wstringstream wss;
		wss << i;
		
		nums[i].set(wss.str().c_str(), ((i + 1) % 3) * 60, i / 3 * 60 + 60, 30, 30, &win);
		wss.clear();
	}
	i = 7;
	 
	edit.set(0, 400, 400, 100, 100, &win);
	  Typer.set(L"asdasda", 190, 190, 90, 90, &win);
	  wstring addo = Typer.GetText();

	  for ( i = 1; i < 10; i++)
	  {

	  win.AddFunc(i, create_function());
	  }
	 // win.AddFunc(1, func, { &sta});
	//
	////adding things needed at start
	//
	//  addcontrols(Hwindow);
	//  addmenu(Hwindow);
	//
	//
	//
	//
	////massage loop
	//MSG msg;
	//while (GetMessage(&msg,Hwindow,NULL,NULL)>0)
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessageW(&msg);
	//}
	//

	  win.start(); 
	return 0;
}
long color = RGB(0, 0, 0);

DWORD CtrlID;
wstring arr;
//LRESULT CALLBACK  winproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
//{
//
//	switch (msg)
//	{
//	case WM_CTLCOLORSTATIC:
//	{
//
//		HDC hdcStatic = (HDC)wp;
//		SetTextColor(hdcStatic, color);
//		SetBkColor(hdcStatic, RGB(250, 250, 0));
//		return (INT_PTR)CreateSolidBrush(RGB(250, 250, 0));
//	}
//
//
//
//	case WM_COMMAND:
//
//		switch (wp)
//		{
//		case 1:
//			MessageBeep(MB_OK);
//			break;
//		case 2:
//			 MessageBox(hwnd,L" you sure???",L"L",MB_YESNO);
//			break;
//		case 3:
//			
//			break;
//		case 4:
//			break;
//
//		case 5:
//
//			
//			
//			
//			
//			break;
//		
//		}
//
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProcW(hwnd, msg, wp, lp);
//	}
//	return DefWindowProcW(hwnd, msg, wp, lp);
//
//}
//void addmenu(MainWindow& parent)
//{
//
//
//	Menu file(&parent, L"file", 1,true);
//	Menu quit(&parent, L"quit", 2, false);
//	file.destroy();
//	file.AddSubMenu(L"new",2);
//	quit.AddSubMenu(L"yes", 3);
//	quit.AddSubMenu(L"no", 0);
//	file.AddSubMenu(L"change title", 4);
//
//
//}

void addcontrols(MainWindow& hwnd)
{
	
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

//figure how to destroy a menu or make it more logical that they are indestructable.

//at the end: add namespace to cover all the framework
