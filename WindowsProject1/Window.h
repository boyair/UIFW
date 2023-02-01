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

		Window(const wstring& Text, int x, int y, int width, int height);
		Window(wstring&& Text, int x, int y, int width, int height);
		Window();
	public:
		void SetText(wstring&& Text);
		void SetText(const wstring& Text);
		RECT GetRECT();
		void Destroy();
		void hide();
		void show();
	};

}