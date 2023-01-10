#pragma once
#include"MainWindow.h"
#include <thread>


class ExtraWindow:public MainWindow
{
	friend void HandleOnThread(ExtraWindow& window);
	friend class ChildWindow;
	
public:
	DWORD MainID = GetCurrentThreadId();
	std::thread procthread ;
	bool started = false;
	ExtraWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B);
	void start() override {};
	~ExtraWindow();

};

