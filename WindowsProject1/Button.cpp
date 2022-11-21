#include "Button.h"

void Button::place()
{
	if (!parent) return;
	Box = CreateWindowW(L"button", text, style, x, y, width, height, parent, HMENU(id), NULL, NULL);

}

Button::Button(int id):ChildWindow(),id(id)
{
	text = new wchar_t[textlength+1];

}

Button::Button(const wchar_t* Text, int x, int y, int width, int height, int id, HWND* parent):ChildWindow(Text, x, y, width, height, parent),id(id)
{
	if (!parent) return;
	Box = CreateWindowW(L"button", Text, style, x, y, width, height, *parent, HMENU(id), NULL, NULL);
	text = new wchar_t[textlength + 1];
}

void Button::set(const wchar_t* Text, int x, int y, int width, int height,int id, HWND* parent)
{
	if (!parent) return;
	this->parent = *parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->id = id;

	const unsigned int newsize = wcsnlen_s(Text, 0xFFFFFF);
	if (newsize > textlength)
	{
		wchar_t* save = text;
		text = new wchar_t[newsize + 1];
		delete[] save;
		textlength = newsize;
	}
	wcscpy_s(text, textlength + 1, Text);

	Box = CreateWindowW(L"button", Text, style, x, y, width, height, *parent, HMENU(id), NULL, NULL);

}

void Button::addimage(const wchar_t* name)
{
	std::wstring fullname = std::wstring(name) + std::wstring(L".bmp");
	HBITMAP image = (HBITMAP)LoadImageW(NULL, fullname.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	if (!image) return;
	DestroyWindow(Box);
	style = style | BS_BITMAP;
	place();
	SendMessageW(Box, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
}

Button::~Button()
{
	delete[] text;

	DestroyWindow(Box);
}
