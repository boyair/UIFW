#pragma once
#include <functional>
#include <vector>
#include <utility>
//#include <thread>
#include "Window.h"

class MainWindow: public Window
{
	friend class ChildWindow;
	friend class EW;
	friend class Button;
	
	 WNDCLASSW CLS = { 0 };
	static LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	 public:
	 MainWindow(const wstring& Text, int x, int y, int width, int height);
	 MainWindow(const wstring& Text, int x, int y, int width, int height,int R,int G,int B);
	 HMENU menu = CreateMenu();
	 std::vector<HMENU> ChildMenus;



	 void AddMenu(const wstring& name, long id, bool parent);
	 bool AddSubMenu(const wstring& name,int menuindex, long id);

	 void start();
	 bool AddFunc(int id, void(*func)());


};

