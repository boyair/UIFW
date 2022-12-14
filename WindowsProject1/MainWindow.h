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

	 void start();
	 bool AddFunc(int id, void(*func)());


};

