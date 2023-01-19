#include "Button.h"


namespace UIFW {



	void Button::place()
	{
		if (&parent)
			Hwnd = CreateWindowW(L"button", text.c_str(), style, x, y, width, height, parent->Hwnd, HMENU(id), NULL, NULL);


	}

	void Button::SendImage()
	{
		SendMessageW(Hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img->BM);
	}



	Button::Button(long long id) :ChildWindow(), id(id)
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

	void Button::Addimage(image& img)
	{
		//returns if window dosent exist.
		this->img = &img;
		if (!parent) return;

		style = style | BS_BITMAP;
		SetWindowLongPtr(Hwnd, GWL_STYLE, style);
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);
	//	AddImageExtra();
		SendMessageW(Hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);
	}




	Button::~Button()
	{
		DestroyWindow(Hwnd);
	}
}