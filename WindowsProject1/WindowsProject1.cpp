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
 ChildWindow edit;
 Button nums[10] = {(0),(1),(2),(3),(4),(5),(6),(7),(8),(9)};
 Button nums2[10] = { (0),(1),(2),(3),(4),(5),(6),(7),(8),(9) };
 ChildWindow tester;
 int i;
 MainWindow win(L"W working window", 2000, 20, 1000, 1000, 0, 0, 0);
 MainWindow win2(L"W working window2", 1000, 20, 1000, 1000, 255, 0, 0);

 Button move(5);
 Button Typer(1);

HWND Hedit;


void(*buttons[])() = { 
	[]() {edit.SetText(edit.GetText() + L"0"); },
	[]() {edit.SetText(edit.GetText() + L"1"); win.RemoveMenuBar(); },[]() {edit.SetText(edit.GetText() + L"2"); },[]() {edit.SetText(edit.GetText() + L"3"); },
[]() {edit.SetText(edit.GetText() + L"4"); },[]() {edit.SetText(edit.GetText() + L"5"); },[]() {edit.SetText(edit.GetText() + L"6"); },
[]() {edit.SetText(edit.GetText() + L"7"); },[]() {edit.SetText(edit.GetText() + L"8"); },[]() {edit.SetText(edit.GetText() + L"9"); },


};


int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{

	
	for (int i = 0; i < 10; i++)
	{
		std::wstringstream wss;
		wss << i;
		
		nums[i].set(wss.str().c_str(), ((i % 3) +1)* 60, i / 3 * 60 + 60, 30, 30, &win);
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
	
	//HMENU menu = CreateMenu();
	//AppendMenuW(menu, MF_STRING, 1,L"file");
	//SetMenu(win.Hwnd, menu);
	win.AddMenu(L"quit", 11, 0);
	win.AddMenu(L"file", 1, true);
	win.AddSubMenu(L"sub", 0, 1);
	edit.set(0, 400, 400, 400, 100, &win);
	
	  Typer.set(L"asdasda", 230, 190, 90, 90, &win);
	  wstring addo = Typer.GetText();

	

	  win.AddFunc(11, []() {MessageBox(win.Hwnd, L"title", L"Text", MB_YESNO); });
	  
	

	  win.start(); 
	  win2.start();
	return 0;
}
