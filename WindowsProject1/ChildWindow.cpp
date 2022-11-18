#include "ChildWindow.h"

ChildWindow::ChildWindow() :style(WS_VISIBLE | WS_CHILD), textlength(10),x(0),y(0),width(0),height(0),parent(NULL),Box(NULL),text(NULL)
{
}

ChildWindow::ChildWindow(const wchar_t* Text, int x, int y, int width, int height,  HWND* parent): parent(*parent), x(x), y(y), width(width), height(height), style(WS_VISIBLE | WS_CHILD), textlength(10), Box(NULL), text(NULL)
{
}

void ChildWindow::SetText(const wchar_t* Text)
{
	if (!Box || !parent) return;
	
	const unsigned int newsize = wcsnlen_s(Text,0xFFFFFF);
	if (newsize > textlength)
	{
		wchar_t* save = text;
		text = new wchar_t[newsize + 1];
		delete[] save;
	}
	wcscpy_s(text, newsize + 1,Text );


	SetWindowTextW(Box,text);
}

void ChildWindow::Move(int DX, int DY)
{
	x += DX; y += DY;
}

void ChildWindow::resize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void ChildWindow::Remove()
{
	DestroyWindow(Box);
}

void ChildWindow::AddBorder()
{

	GetWindowText(Box, text, textlength);
	DestroyWindow(Box);
	style = style | WS_BORDER;
	place();
}


void ChildWindow::RemoveBorder()
{
	if (style == (style & ~ES_AUTOHSCROLL)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~ES_AUTOHSCROLL;
	place();
}