#pragma once
#include "ChildWindow.h"
class Button: public ChildWindow
{
	int id;
	void place();



public:
	Button(int id);
	Button(const wchar_t* Text, int x, int y, int width, int height,int id, HWND* parent);
	void set(const wchar_t* Text, int x, int y, int width, int height, int id, HWND*parent);
	void addimage(const wchar_t* name);
	~Button();


};

