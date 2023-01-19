#include "ChildWindow.h"

namespace UIFW {

	ChildWindow::ChildWindow() :Window(), parent(NULL), img(NULL), winmade(CreateEvent(NULL, FALSE, FALSE, NULL))
	{
		style = (WS_VISIBLE | WS_CHILD);
	}



	ChildWindow::ChildWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent) :Window(Text, x, y, width, height), parent(parent)
	{
		style = (WS_VISIBLE | WS_CHILD);
		placeExtra();
	}

	ChildWindow::ChildWindow(wstring&& Text, int x, int y, int width, int height, MainWindow* parent) : Window(std::move(Text), x, y, width, height), parent(parent)
	{
		style = (WS_VISIBLE | WS_CHILD);
		placeExtra();
	}


	void ChildWindow::place()
	{
		if (parent)
			Hwnd = CreateWindowW(L"static", text.c_str(), style, x, y, width, height, parent->Hwnd, NULL, NULL, NULL);

	}

	void ChildWindow::placeExtra()
	{
		//send to parent window to make the window if its on a different thread.
		if (GetCurrentThreadId() != GetWindowThreadProcessId(parent->Hwnd, 0))
		{
			PostMessage(parent->Hwnd, WM_USER + 1, 1, (LPARAM)this);
			WaitForSingleObject(winmade, INFINITE);
			ResetEvent(winmade);
			return;
		}
		place();
	}

	void ChildWindow::destroyExtra()
	{
		//send to parent window to destroy the window if its on a different thread.
		if (GetCurrentThreadId() != GetWindowThreadProcessId(parent->Hwnd, 0))
		{
			PostMessage(parent->Hwnd, WM_USER + 1, 2, (LPARAM)this);
			WaitForSingleObject(winmade, INFINITE);
			ResetEvent(winmade);
			return;
		}
		Destroy();

	}

	void ChildWindow::AddImageExtra()
	{
		if (GetCurrentThreadId() != GetWindowThreadProcessId(parent->Hwnd, 0))
		{
			PostMessage(parent->Hwnd, WM_USER + 1, 3, (LPARAM)this);
			return;
		}
		SendImage();
	}

	void ChildWindow::SendImage()
	{
		SendMessageW(Hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img->BM);
	}









	void ChildWindow::Addimage(image& img)
	{
		if (!parent->Hwnd || style == (style | SS_BITMAP)) return;

		style = style | SS_BITMAP;
		this->img = &img;
		SetWindowLongPtr(Hwnd, GWL_STYLE, style);
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);
		SendImage();
		//AddImageExtra();
	}





	void ChildWindow::Move(int DX, int DY)
	{

		x += DX; y += DY;
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);


	}







	void ChildWindow::E_Destroy()
	{
		destroyExtra();

	}

	void ChildWindow::resize(int width, int height)
	{
		this->width = width;
		this->height = height;
		SetWindowPos(Hwnd, 0, x, y, width, height, 0);
	}

	void ChildWindow::Remove()
	{
		DestroyWindow(Hwnd);


	}

	void ChildWindow::AddBorder()
	{
		style = style | WS_BORDER;
		if (!Hwnd) return;
		SetWindowLongPtr(Hwnd, GWL_STYLE, style);
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);

	}




	void ChildWindow::RemoveBorder()
	{
		style = style & ~ES_AUTOHSCROLL;
		if (!Hwnd) return;
		SetWindowLongPtr(Hwnd, GWL_STYLE, style);
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);
	}

	void ChildWindow::Reposition(int x, int y)
	{


		this->x = x;
		this->y = y;

		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);



	}

	const wstring& ChildWindow::GetText() const
	{
		return text;
	}


	void ChildWindow::set(const wstring& Text, int x, int y, int width, int height, MainWindow* parent)
	{
		if (!parent) return;
		this->parent = parent;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;

		text = Text;




		placeExtra();
	}

	void ChildWindow::set(wstring&& Text, int x, int y, int width, int height, MainWindow* parent)
	{
		if (!parent) return;
		this->parent = parent;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;

		text = std::move(Text);

		placeExtra();

	}
}





