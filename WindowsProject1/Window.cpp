#include "Window.h"
namespace UIFW
{
	Window::Window(const wstring& Text, int x, int y, int width, int height) : x(x), y(y), width(width), height(height), Hwnd(NULL), text(Text), style(WS_VISIBLE)
	{
	}

	Window::Window(wstring&& Text, int x, int y, int width, int height) : x(x), y(y), width(width), height(height), Hwnd(NULL), text(std::move(Text)), style(WS_VISIBLE)
	{
	}

	Window::Window() :x(0), y(0), width(0), height(0), Hwnd(NULL), style(WS_VISIBLE)
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

	RECT Window::GetRECT()
	{
		RECT rct;
		GetWindowRect(Hwnd, &rct);
		return rct;
	}

	void Window::Destroy()
	{
		DestroyWindow(Hwnd);
		Hwnd = nullptr;

	}

	const wstring& Window::GetText() const
	{
		return text;
	}

	void Window::Hide()
	{
		ShowWindow(Hwnd, 0);
	}
	void Window::Show()
	{
		ShowWindow(Hwnd, 1);
	}
	void Window::Move(int DX, int DY)
	{
		x += DX; y += DY;
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED | SWP_NOSIZE);
	}

	void Window::Resize(int width, int height)
	{
		this->width = width;
		this->height = height;
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_NOMOVE);
	}


	void Window::Reposition(int x, int y)
	{
		this->x = x;
		this->y = y;
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED|SWP_NOSIZE);
	}

	bool Window::Exists()
	{
		return Hwnd;
	}

}

