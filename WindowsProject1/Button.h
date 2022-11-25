#pragma once
#include "ChildWindow.h"
class Button: public ChildWindow
{
	long long id;
	void place();



public:
	Button(long long id);
	Button(const wchar_t* Text, int x, int y, int width, int height, long long id, HWND* parent);
	void addimage(const wchar_t* name);
	~Button();


};

