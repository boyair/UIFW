#pragma once
#include <functional>
#include <vector>
#include <utility>
//#include <thread>
#include "Window.h"
LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

class MainWindow: public Window
{
	
	 WNDCLASSW CLS = { 0 };


	 public:
	 MainWindow(const wstring& Text, int x, int y, int width, int height);
	 MainWindow(const wstring& Text, int x, int y, int width, int height,int R,int G,int B);

	 void start();
	 bool AddFunc(int id, void(*func)());


};

