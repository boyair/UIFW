#include "Button.h"






void Button::place() 
{
	if (!parent) return;
	Hwnd = CreateWindowW(L"button", text.c_str(), style, x, y, width, height, parent->Hwnd, HMENU(id), NULL, NULL);
	

}

Button::Button(long long id):ChildWindow(),id(id)
{

}

Button::Button(const wstring& Text, int x, int y, int width, int height, long long id, MainWindow* parent)  
	:id(id)
{	


	//sets the variables
	text = Text;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->parent = parent;
	//place the button
	placeExtra();

}

Button::Button(wstring&& Text, int x, int y, int width, int height, long long id, MainWindow* parent) 
	: id(id)
{
	//sets the variables
	text = std::move(Text);
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->parent = parent;
	//place the button
	placeExtra();
}

void Button::addimage( image& img)
{
	//returns if window dosent exist.
	if (!parent || !Hwnd) return;

	style = style | BS_BITMAP;
	DestroyWindow(Hwnd);
	place();
	SendMessageW(Hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);

}




Button::~Button()
{
	DestroyWindow(Hwnd);
}
