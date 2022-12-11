#pragma once
#include <Windows.h>
#include "wstring.h"
#include "image.h"
class Window
{
	protected:
	wstring text;
	int x, y, width, height;
	HWND Hwnd;
	unsigned long style;

public:
	Window(const wstring& Text, int x, int y, int width, int height);
	Window(wstring&& Text, int x, int y, int width, int height);
	Window();
};

