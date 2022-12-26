#pragma once
#include <functional>
#include <vector>
#include <utility>
#include "Window.h"
//#include <thread>

class MainWindow: public Window
{
	friend class ChildWindow;
	friend class EW;
	friend class Button;
	friend LRESULT CALLBACK NonStaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	 WNDCLASSW CLS = { 0 };
	 LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	  LONG_PTR save;
	  MSG msg;
	 public:
	 MainWindow(const wstring& Text, int x, int y, int width, int height);
	 MainWindow(const wstring& Text, int x, int y, int width, int height,int R,int G,int B,wstring classname);
	 HMENU menu = CreateMenu();
	 std::vector<HMENU> ChildMenus;
	  std::vector<std::pair<int, void(*)()>> functionallitys;


	 void AddMenu(const wstring& name, long id, bool parent);
	 bool AddSubMenu(const wstring& name,int menuindex, long id);
	 void RemoveMenuBar();

	 virtual void start();
	 bool AddFunc(int id, void(*func)());


};

