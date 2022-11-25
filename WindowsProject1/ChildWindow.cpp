#include "ChildWindow.h"

HBITMAP image;
ChildWindow::ChildWindow() :style(WS_VISIBLE | WS_CHILD), textlength(10),x(0),y(0),width(0),height(0),parent(NULL),Box(NULL),text(NULL)
{
	text = new wchar_t[textlength + 1];
}

ChildWindow::ChildWindow(const wchar_t* Text, int x, int y, int width, int height, HWND* parent) : parent(*parent), x(x), y(y), width(width), height(height), style(WS_VISIBLE | WS_CHILD), textlength(10), Box(NULL), text(NULL)
{

	

		if (!parent) return;
	text = new wchar_t[max(textlength, wcsnlen_s(Text, 0xFFFFFF)) + 1];
	textlength = max(textlength, wcsnlen_s(Text, 0xFFFFFF));

		wcscpy_s(text, textlength, Text);

		place();
}

void ChildWindow::place()
{
	if (parent)
		Box = CreateWindowW(L"static", text, style, x, y, width, height, parent, NULL, NULL, NULL);
}

void ChildWindow::SetText(const wchar_t* Text)
{
	
	if (!Box || !parent) return;	//if the window handler or parent window does not exist return.

	// if the text length is longer then allocated reallocated text member veriable in a larger block of memory.
	const unsigned int newsize = wcsnlen_s(Text,0xFFFFFF);
	if (newsize > textlength)
	{
		wchar_t* save = text;
		text = new wchar_t[newsize + 1];
		delete[] save;
	}

	// copy text content to member veriable and set the window text.
	wcscpy_s(text, newsize + 1,Text );
	SetWindowTextW(Box,text);
}

void ChildWindow::addimage(const wchar_t* name)
{
	if (!parent) return;
	std::wstring fullname = std::wstring(name) + std::wstring(L".bmp");
	HBITMAP image = (HBITMAP)LoadImageW(NULL, fullname.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	DestroyWindow(Box);
	style = style | SS_BITMAP;
	Box = CreateWindowW(L"static", text, style, x, y, width, height, parent, NULL, NULL, NULL);
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
	GetWindowText(Box, text, width / 8 + 1);
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

void ChildWindow::set(const wchar_t* Text, int x, int y, int width, int height, HWND* parent)
{
	if (!parent) return;
	this->parent = *parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	const unsigned int newsize = wcsnlen_s(Text, 0xFFFFF);
	if (newsize > textlength)
	{
		wchar_t* save = text;
		text = new wchar_t[newsize + 1];
		delete[] save;
		textlength = newsize;
	}
	wcscpy_s(text, textlength + 1, Text);




	place();
}
