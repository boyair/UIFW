#include "Window.h"

Window::Window(const wstring& Text, int x, int y, int width, int height): x(x), y(y), width(width), height(height), Hwnd(NULL), text(Text), style(WS_VISIBLE)
{
}

Window::Window(wstring&& Text, int x, int y, int width, int height) : x(x), y(y), width(width), height(height), Hwnd(NULL), text(std::move(Text)), style(WS_VISIBLE)
{
}

Window::Window():x(0), y(0), width(0), height(0), Hwnd(NULL),style(WS_VISIBLE)
{
}

void Window::SetText(wstring&& Text)
{
	//if the window handler or parent window does not exist return.


	text = std::move(Text);
	//if (!Hwnd) return;
	SetWindowTextW(Hwnd, text.c_str());
	
}

void Window::SetText(const wstring& Text)
{
	//if (!Hwnd) return;	//if the window handler or parent window does not exist return.
	text = Text;
	SetWindowTextW(Hwnd, text.c_str());
	
}
