#include "ChildWindow.h"

ChildWindow::ChildWindow() :style(WS_VISIBLE | WS_CHILD),x(0),y(0),width(0),height(0),parent(NULL),Box(NULL)
{
	
}

ChildWindow::ChildWindow(const wstring& Text, int x, int y, int width, int height, HWND* parent) : parent(*parent), x(x), y(y), width(width), height(height), style(WS_VISIBLE | WS_CHILD), Box(NULL),text(Text)
{
		place();
}

ChildWindow::ChildWindow(wstring&& Text, int x, int y, int width, int height, HWND* parent) : parent(*parent), x(x), y(y), width(width), height(height), style(WS_VISIBLE | WS_CHILD), Box(NULL), text((wstring&&)Text)
{
	place();
}


void ChildWindow::place()
{
	if (parent)
		Box = CreateWindowW(L"static", text.c_str(), style, x, y, width, height, parent, NULL, NULL, NULL);
}

void ChildWindow::SetText(const wstring& Text)
{
	
	if (!Box || !parent) return;	//if the window handler or parent window does not exist return.
	text = Text;
	SetWindowTextW(Box,text.c_str());
}

void ChildWindow::SetText(wstring&& Text)
{

		//if the window handler or parent window does not exist return.
		if (!Box || !parent) return;
		

		text = std::move(Text);
		SetWindowTextW(Box, text.c_str());
}


void ChildWindow::addimage(const image& img)
{
	if (!parent) return;
	
	style = style | SS_BITMAP;
	DestroyWindow(Box);
	place();
	SendMessageW(Box, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);
}





void ChildWindow::Move(int DX, int DY)
{
	DestroyWindow(Box);

	x += DX; y += DY;
	place();

}

void ChildWindow::resize(int width, int height)
{
	DestroyWindow(Box);
	this->width = width;
	this->height = height;
	place();
}

void ChildWindow::Remove()
{
	DestroyWindow(Box);

	
}

void ChildWindow::AddBorder()
{
	style = style | WS_BORDER;
	if (!Box) return;
	DestroyWindow(Box);
	place();
}


void ChildWindow::RemoveBorder()
{
	style = style & ~ES_AUTOHSCROLL;
	if (!Box) return;
	DestroyWindow(Box);
	place();
}

void ChildWindow::Reposition(int x, int y)
{
	
	DestroyWindow(Box);

	this->x = x;
	this->y = y;
	place();


}

void ChildWindow::set(const wstring& Text, int x, int y, int width, int height, HWND* parent)
{
	if (!parent) return;
	this->parent = *parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	text = Text;




	place();
}

void ChildWindow::set(wstring&& Text, int x, int y, int width, int height, HWND* parent)
{
	if (!parent) return;
	this->parent = *parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	text = std::move(Text);




	place();
}
