#pragma once
#include <Windows.h>
#include "wstring.h"
#include "image.h"
class Window
{
	protected:
	wstring text;
	int x, y, width, height;
	unsigned long style;

public:
	HWND Hwnd;
	Window(const wstring& Text, int x, int y, int width, int height);
	Window(wstring&& Text, int x, int y, int width, int height);
	Window();
	void SetText(wstring&& Text);
	void SetText(const wstring& Text);
};

