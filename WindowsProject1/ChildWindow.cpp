#include "ChildWindow.h"



ChildWindow::ChildWindow() :Window(), parent(NULL)
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
	MSG msg;
}

void ChildWindow::SetText(const wstring& Text)
{
	
	if (!Hwnd || !parent->Hwnd) return;	//if the window handler or parent window does not exist return.
	text = Text;
	SetWindowTextW(Hwnd,text.c_str());
}

void ChildWindow::SetText(wstring&& Text)
{

		//if the window handler or parent window does not exist return.
		if (!Hwnd || !parent->Hwnd) return;
		

		text = std::move(Text);
		SetWindowTextW(Hwnd, text.c_str());
}


void ChildWindow::SetColorText(int R, int G, int B)
{

}

void ChildWindow::addimage(const image& img)
{
	if (!parent->Hwnd || style == (style|SS_BITMAP)) return;
	
	style = style | SS_BITMAP;

	DestroyWindow(Hwnd);
	place();
	SendMessageW(Hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);
}





void ChildWindow::Move(int DX, int DY)
{
	DestroyWindow(Hwnd);

	x += DX; y += DY;
	place();

}

void ChildWindow::resize(int width, int height)
{
	DestroyWindow(Hwnd);
	this->width = width;
	this->height = height;
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
	
	DestroyWindow(Hwnd);

	this->x = x;
	this->y = y;
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




	place();
}

void ChildWindow::set(const wstring& Text, int x, int y, int width, int height, ExtraWindow* parent)
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
