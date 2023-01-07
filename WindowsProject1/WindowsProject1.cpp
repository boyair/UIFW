#include <sstream>
#include<thread>
#include "ExtraWindow.h"
#include "Menu.h"
#include "EW.h"
#include "Button.h"
#include "image.h"
#include "MainWindow.h"


 ChildWindow edit;
 EW extest;
 Button nums[10] = {(0),(1),(2),(3),(4),(5),(6),(7),(8),(9)};
 Button nums2[10] = { (0),(1),(2),(3),(4),(5),(6),(7),(8),(9) };
 ChildWindow colors[10];
 ChildWindow tester;
 int i;
image img(L"B.bmp");
 MainWindow win(L"W working window1", 500, 20, 1000, 1000,img);
 ExtraWindow win2(L"W working window2", 1000, 20, 1000, 1000, 255, 0, 0);
 ExtraWindow win3(L"W working window3", 2000, 20, 1000, 1000, 0, 255, 0);
 
 Button move(5);
 Button Typer(1);




void(*buttons[])() = { 
	[]() {edit.SetText(edit.GetText() + L"0"); },
	[]() {edit.SetText(edit.GetText() + L"1"); 
win.RemoveMenuBar(); }, 

[]() {edit.SetText(edit.GetText() + L"2"); },

[]() {edit.SetText(edit.GetText() + L"3");
win2.RemoveMenuBar(); 

},
[]() {

	//edit.E_Destroy();
	//win2.AddMenu(L"FILE", 4, false);
//	img.LoadFromFile(L"B");
nums2[7].Remove();
edit.SetText(edit.GetText() + L"4");
//edit.AddBorder();
extest.Reposition(900, 900);
edit.Reposition(900, 900);
}

,[]() {edit.SetText(edit.GetText() + L"5"); 

//extest.AddBorder();
},[]() {edit.SetText(edit.GetText() + L"6"); },
[]() {edit.SetText(edit.GetText() + L"7"); },[]() {edit.SetText(edit.GetText() + L"8"); },[]() {edit.SetText(edit.GetText() + L"9"); },


};
int main()

{

	for (int i = 0; i < 10; i++)
	{
		std::wstringstream wss;
		wss << i;

		nums[i].set(wss.str().c_str(), ((i % 3) + 1) * 60, i / 3 * 60 + 60, 30, 30, &win);
		win.AddFunc(i, buttons[i]);
		wss.clear();
	}
	for (int i = 0; i < 10; i++)
	{
		std::wstringstream wss;
		wss << i;

		nums2[i].set(wss.str().c_str(), ((i % 3) + 1) * 60, i / 3 * 60 + 60, 30, 30, &win2);
		
		win2.AddFunc(i, buttons[i]);
		wss.clear();
	}

	
	win2.SetColor_EW_BK(0, 255, 0);
	win2.SetColor_EW_Text(255, 0, 0);
	//extest.AddVerticalScrolling();
	
	extest.set(L"LOL", 500, 500, 90, 90, &win2);
	
	win.AddMenu(L"quit", 11, 0);
	win.AddMenu(L"file", 1, true);
	win.AddSubMenu(L"sub", 0, 1);
	edit.set(L"kok", 400, 400, 400, 100, &win);
	win2.SetText(L"changed text");
	Typer.set(L"LOL", 230, 190, 90, 90, &win);
	//  nums2->SetText(L"n");

	win2.AddFunc(1, buttons[1]);
	win3.AddFunc(1, buttons[2]);
	win2.AddMenu(L"Test", 5, false);
	win.AddFunc(11, []() {int i = MessageBox(win.Hwnd, L"title", L"Text", MB_YESNO|MB_ICONERROR|MB_SYSTEMMODAL);

	if (i == 6)  win2.Destroy(); });

	win.start();

	

}

int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{

	main();
	
}
