#include "ChildWindow.h"

HBITMAP image;
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


void ChildWindow::addimage(const wstring& name)
{
	if (!parent) return;
	std::wstring fullname = std::wstring(name.c_str()) + std::wstring(L".bmp");
	HBITMAP image = (HBITMAP)LoadImageW(NULL, fullname.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	DestroyWindow(Box);
	style = style | SS_BITMAP;
	Box = CreateWindowW(L"static", text.c_str(), style, x, y, width, height, parent, NULL, NULL, NULL);
	SendMessageW(Box, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
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
	if (style == (style | WS_BORDER)) return;
	DestroyWindow(Box);
	style = style | WS_BORDER;
	place();
}


void ChildWindow::RemoveBorder()
{
	if (style == (style & ~WS_BORDER)) return;
	DestroyWindow(Box);
	style = style & ~ES_AUTOHSCROLL;
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
