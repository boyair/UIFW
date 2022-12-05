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
	DestroyWindow(Box);
}
