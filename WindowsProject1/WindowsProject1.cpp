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
 MainWindow win(L"W working window", 2000, 20, 1000, 1000, 255, 0, 0);
 Button move(5);
 Button Typer(1);

HWND Hedit;

//int main()
//{
//	MainWindow Main(R,G,B,x,y,width,height)
//
//
//
//}


void create_function(void)
{
			win.SetText(L"guchi");
	

}



int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{

	
	for (size_t i = 0; i < 9; i++)
	{
		std::wstringstream wss;
		wss << i;
		
		nums[i].set(wss.str().c_str(), ((i % 3) +1)* 60, i / 3 * 60 + 60, 30, 30, &win);
		wss.clear();
	}
	
	//HMENU menu = CreateMenu();
	//AppendMenuW(menu, MF_STRING, 1,L"file");
	//SetMenu(win.Hwnd, menu);
	win.AddMenu(L"sfile", 1, true);
	win.AddSubMenu(L"sub", 0, 1);
	edit.AddVerticalScrolling();
	edit.set(0, 400, 400, 400, 100, &win);
	edit.SetText(L"text");

	  Typer.set(L"asdasda", 230, 190, 90, 90, &win);
	  wstring addo = Typer.GetText();

	  for ( i = 1; i < 10; i++)
	  {

	  win.AddFunc(i, create_function);
	  }
	

	  win.start(); 
	return 0;
}
