#pragma once
#include "ChildWindow.h"
class Button: public ChildWindow
{
	long long id;
	void place();
	static long BTBKCLR, BTTXCLR;


public:
	Button(long long id);
	Button(const wstring& Text, int x, int y, int width, int height, long long id, HWND* parent);
	Button( wstring&& Text, int x, int y, int width, int height, long long id, HWND* parent);
	void addimage(const image& img);
	~Button();


};

