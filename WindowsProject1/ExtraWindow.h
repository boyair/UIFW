#pragma once
#include"MainWindow.h"
#include <thread>
class ExtraWindow:public MainWindow
{
	friend LRESULT CALLBACK NonStaticWindowProcThread(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend void CreateWindow1(ExtraWindow& window);
public:
	std::thread procthread ;
	bool started = false;
	ExtraWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B,wstring classname);
	void start() override;
	~ExtraWindow();

};

