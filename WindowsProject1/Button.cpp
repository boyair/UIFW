#include "Button.h"

void Button::place()
{
	if (!parent) return;
	Box = CreateWindowW(L"button", text.c_str(), style, x, y, width, height, parent, HMENU(id), NULL, NULL);

}

Button::Button(long long id):ChildWindow(),id(id)
{

}

Button::Button(const wstring& Text, int x, int y, int width, int height, long long id, HWND* parent):ChildWindow(Text, x, y, width, height, parent),id(id){	}

Button::Button(wstring&& Text, int x, int y, int width, int height, long long id, HWND* parent) :ChildWindow((wstring&&) Text, x, y, width, height, parent), id(id)
{
}

void Button::addimage(const image& img)
{
	if (!parent || style == (style | BS_BITMAP)) return;

	style = style | BS_BITMAP;
	DestroyWindow(Box);
	place();
	SendMessageW(Box, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);

}





Button::~Button()
{
	DestroyWindow(Box);
}
