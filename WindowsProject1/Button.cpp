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

	Box = CreateWindowW(L"button", Text, style, x, y, width, height, *parent, HMENU(id), NULL, NULL);

}

Button::~Button()
{
	delete[] text;

	DestroyWindow(Box);
}
