#include "ChildWindow.h"



ChildWindow::ChildWindow() :Window(), parent(NULL),img(NULL)
{
	style = (WS_VISIBLE | WS_CHILD);
}

ChildWindow::ChildWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent) :Window(Text,x,y,width,height) ,parent(parent)
{
	style = (WS_VISIBLE | WS_CHILD);
	place();
}

ChildWindow::ChildWindow(wstring&& Text, int x, int y, int width, int height, MainWindow* parent) :  Window(std::move(Text), x, y, width, height), parent(parent)
{
	style = (WS_VISIBLE | WS_CHILD);

	place();
}


void ChildWindow::place()
{
	if (parent)
		Hwnd = CreateWindowW(L"static", text.c_str(), style, x, y, width, height, parent->Hwnd, NULL, NULL, NULL);
}

void ChildWindow::placeExtra()
{
#if _DEBUG

#endif
	
	PostMessage(parent->Hwnd, WM_USER+1, 1, (LPARAM)this);
}

void ChildWindow::destroyExtra()
{
	PostMessage(parent->Hwnd, WM_USER + 1, 2, (LPARAM)this);
}

void ChildWindow::SendImageExtra()
{
	PostMessage(parent->Hwnd, WM_USER + 1, 4, (LPARAM)this);
}

void ChildWindow::SetTextExtra()
{
	PostMessage(parent->Hwnd, WM_USER + 1, 3, (LPARAM)this);
	
}


void ChildWindow::SetText(const wstring& Text)
{

	if (!Hwnd || !parent->Hwnd) return;	//if the window handler or parent window does not exist return.
	text = Text;

	SetWindowTextW(Hwnd, text.c_str());
	
}

void ChildWindow::SetText(wstring&& Text)
{

		//if the window handler or parent window does not exist return.
		if (!Hwnd || !parent->Hwnd) return;
		

		text = std::move(Text);
		//RECT rtc{ x,y,x + width,y + height };
		//RedrawWindow(Hwnd, &rtc, 0, RDW_ERASE);
		
		SetWindowTextW(Hwnd, text.c_str());
		
}




void ChildWindow::addimage(image& img)
{
	if (!parent->Hwnd || style == (style|SS_BITMAP)) return;
	
	style = style | SS_BITMAP;
	this->img = &img;
	DestroyWindow(Hwnd);
	place();
	SendMessageW(Hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);
}





void ChildWindow::Move(int DX, int DY)
{

	x += DX; y += DY;
	DestroyWindow(Hwnd);
	place();

}

void ChildWindow::E_Move(int DX, int DY)
{
	x += DX; y += DY;
	destroyExtra();
	placeExtra();
	
}

void ChildWindow::E_Reposition(int x, int y)
{
	this->x = x;
	this->y = y;
	destroyExtra();
	placeExtra();
}

void ChildWindow::E_set(const wstring& Text, int x, int y, int width, int height, ExtraWindow* parent)
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

void ChildWindow::E_set(wstring&& Text, int x, int y, int width, int height, ExtraWindow* parent)
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

void ChildWindow::E_SetText(const wstring& Text)
{
	text = Text;
	SetTextExtra();
}

void ChildWindow::E_SetText(wstring&& Text)
{
	text = std::move(Text);
	SetTextExtra();
}

void ChildWindow::E_Destroy()
{
	destroyExtra();
}

void ChildWindow::resize(int width, int height)
{
	this->width = width;
	this->height = height;
	DestroyWindow(Hwnd);
	place();
}

void ChildWindow::Remove()
{
	DestroyWindow(Hwnd);

	
}

void ChildWindow::AddBorder()
{
	style = style | WS_BORDER;
	if (!Hwnd) return;
	DestroyWindow(Hwnd);
	place();
}




void ChildWindow::RemoveBorder()
{
	style = style & ~ES_AUTOHSCROLL;
	if (!Hwnd) return;
	DestroyWindow(Hwnd);
	place();
}

void ChildWindow::Reposition(int x, int y)
{
	

	this->x = x;
	this->y = y;
	DestroyWindow(Hwnd);
	place();


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




	place();
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
	
	RECT rct { width,height };


	place();
	InvalidateRect(Hwnd, &rct , TRUE);
}

void ChildWindow::E_addimage( image& img)
{
	//if (!parent->Hwnd || style == (style | SS_BITMAP)) return;
	this->img = &img;
	//style = style | SS_BITMAP;
	SendImageExtra();
	
	//destroyExtra();
	//placeExtra();
	//SendImageExtra();
//	SendMessageW(Hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);
}

void ChildWindow::E_AddBorder()
{
	style = style | WS_BORDER;
	if (!Hwnd) return;
	destroyExtra();
	placeExtra();
}

void ChildWindow::E_RemoveBorder()
{
	style = style & ~ES_AUTOHSCROLL;
	if (!Hwnd) return;
	destroyExtra();
	placeExtra();
}

void ChildWindow::E_resize(int width, int height)
{
	this->width = width;
	this->height = height;
	destroyExtra();
	placeExtra();
}

void ChildWindow::setOnExtra(const wstring& Text, int x, int y, int width, int height, ExtraWindow* parent)
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
