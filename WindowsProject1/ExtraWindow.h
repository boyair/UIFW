#pragma once
#include"MainWindow.h"
#include <thread>


class ExtraWindow:public MainWindow
{
	friend LRESULT CALLBACK NonStaticWindowProcThread(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend void HandleOnThread(ExtraWindow& window);
	friend class ChildWindow;
	LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
public:
	DWORD MainID = GetCurrentThreadId();
	std::thread procthread ;
	bool started = false;
	ExtraWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B);
	
	void start() override {};
	~ExtraWindow();

};

