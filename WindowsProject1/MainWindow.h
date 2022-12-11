#pragma once
#include "Window.h"
#include <vector>
#include <utility>
LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

class MainWindow: public Window
{
	
	 WNDCLASSW CLS = { 0 };
	 std::vector<std::pair<int, void(*)>> fanctionallitys;


	 public:
	 MainWindow(const wstring& Text, int x, int y, int width, int height);
	 MainWindow(const wstring& Text, int x, int y, int width, int height,int R,int G,int B);

};

