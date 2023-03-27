#include "ExternalWindow.h"
namespace UIFW {
	void ExternalWindow::UpdateRECT()
	{
		RECT newrect;
		GetWindowRect(Hwnd, &newrect);
		x = newrect.left;
		y = newrect.top;
		width = newrect.right - x;
		height = newrect.bottom - y;
	}

	ExternalWindow::ExternalWindow(const wstring& name) :Window()
	{
		Hwnd = FindWindow(0, name.c_str());
		if (!Hwnd) return;
		text = name;
		RECT r;
		GetWindowRect(Hwnd, &r);
		x = r.left;
		y = r.top;
		width = r.right - x;
		height = r.bottom - y;




	}

	
	ExternalWindow::ExternalWindow(wstring&& name)
	{
		Hwnd = FindWindow(0, name.c_str());
		if (!Hwnd) return;
		text = std::move(name);
		RECT r;
		GetWindowRect(Hwnd, &r);
		x = r.left;
		y = r.top;
		width = r.right - x;
		height = r.bottom - y;
	}

	bool ExternalWindow::Init(const wstring& name)
	{
		Hwnd = FindWindow(0, name.c_str());
		if (!Hwnd) return false;
		text = name;
		RECT r;
		GetWindowRect(Hwnd, &r);
		x = r.left;
		y = r.top;
		width = r.right - x;
		height = r.bottom - y;
		return true;
	}

	bool ExternalWindow::Init(wstring&& name)
	{
		Hwnd = FindWindow(0, name.c_str());
		if (!Hwnd) return false;
		text = std::move(name);
		RECT r;
		GetWindowRect(Hwnd, &r);
		x = r.left;
		y = r.top;
		width = r.right - x;
		height = r.bottom - y;
		return true;
	}

	POINT ExternalWindow::GetMousePos()
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(Hwnd, &p);

		return p;
	}

	void ExternalWindow::Destroy()
	{
		if (Exists())
			PostMessage(Hwnd, WM_CLOSE, 0, 0);

	}

	bool ExternalWindow::Exists()
	{
		return Hwnd && IsWindow(Hwnd);
	}


	RECT ExternalWindow::GetRECT()
	{
		UpdateRECT();
		return Window::GetRECT();
	}

	void ExternalWindow::Move(int DX, int DY)
	{
		UpdateRECT();
		Window::Move(DX, DY);


	}

	void ExternalWindow::Resize(int width, int height)
	{
		UpdateRECT();
		Window::Resize(width, height);


	}

	void ExternalWindow::Reposition(int x, int y)
	{
		UpdateRECT();
		Window::Reposition(x, y);
	}
};