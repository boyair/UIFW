#pragma once
#include"MainWindow.h"
#include <thread>
enum HandleChild
{
	CW_Place = 1, CW_Destroy, CW_SetText, CW_SendIMage
};
class ChildWindow;
class ExtraWindow:public MainWindow
{
	friend LRESULT CALLBACK NonStaticWindowProcThread(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	friend void HandleOnThread(ExtraWindow& window);
	friend class ChildWindow;
	void ReciveWindowAndHandle();
	ChildWindow* ToHandle = nullptr;
	LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	char ChildFunc = 0;
public:
	DWORD MainID = GetCurrentThreadId();
	std::thread procthread ;
	bool started = false;
	ExtraWindow(const wstring& Text, int x, int y, int width, int height, int R, int G, int B,wstring classname);
	void start() override;
	~ExtraWindow();

};

