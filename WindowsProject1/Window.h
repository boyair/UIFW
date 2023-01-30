#pragma once
#include <Windows.h>
#include "wstring.h"
#include "image.h"
namespace UIFW {
	class Window
	{
	protected:
		HWND Hwnd;
		wstring text;
		int x, y, width, height;
		unsigned long style;

	public:
		Window(const wstring& Text, int x, int y, int width, int height);
		Window(wstring&& Text, int x, int y, int width, int height);
		Window();
		void SetText(wstring&& Text);
		RECT GetRECT();
		void SetText(const wstring& Text);
		void Destroy();
		void hide();
		void show();
	};

}