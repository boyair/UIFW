#pragma once
#include <Windows.h>
#include "wstring.h"
#include "image.h"
class Window
{
	protected:
	wstring name;
	int x, y, width, height;
	HWND Hwnd;
	unsigned long style;

	virtual void place() = 0;
public:
	virtual void addimage(const image& name) = 0;

};

