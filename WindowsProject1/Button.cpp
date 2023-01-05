#include "Button.h"






void Button::place() 
{
	if (!parent) return;
	Hwnd = CreateWindowW(L"button", text.c_str(), style, x, y, width, height, parent->Hwnd, HMENU(id), NULL, NULL);
	

}

Button::Button(long long id):ChildWindow(),id(id)
{

}

Button::Button(const wstring& Text, int x, int y, int width, int height, long long id, MainWindow* parent)  :ChildWindow(Text, x, y, width, height, parent),id(id)  {	}

Button::Button(wstring&& Text, int x, int y, int width, int height, long long id, MainWindow* parent) :ChildWindow((wstring&&) Text, x, y, width, height, parent), id(id)
{
}

//void Button::set(wstring&& Text, int x, int y, int width, int height, MainWindow* parent)
//{
//	if (!parent) return;
//	this->parent = parent;
//	this->x = x;
//	this->y = y;
//	this->width = width;
//	this->height = height;
//
//	text = std::move(Text);
//
//
//
//
//	placeExtra();
//}

void Button::addimage( image& img)
{
	if (!parent || style == (style | BS_BITMAP)) return;

	style = style | BS_BITMAP;
	DestroyWindow(Hwnd);
	place();
	SendMessageW(Hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);

}




Button::~Button()
{
	DestroyWindow(Hwnd);
}
