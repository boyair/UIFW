#include "ChildWindow.h"



ChildWindow::ChildWindow() :Window(), parent(NULL),img(NULL)
{
	style = (WS_VISIBLE | WS_CHILD);
}



ChildWindow::ChildWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent) :Window(Text,x,y,width,height) ,parent(parent)
{
	style = (WS_VISIBLE | WS_CHILD);
	placeExtra();
}

ChildWindow::ChildWindow(wstring&& Text, int x, int y, int width, int height, MainWindow* parent) :  Window(std::move(Text), x, y, width, height), parent(parent)
{
	style = (WS_VISIBLE | WS_CHILD);

	placeExtra();
}


void ChildWindow::place()
{
	if (parent)
		Hwnd = CreateWindowW(L"static", text.c_str(), style, x, y, width, height, parent->Hwnd, NULL, NULL, NULL);
}

void ChildWindow::placeExtra()
{
#if _DEBUG

#endif
	
	SendMessage(parent->Hwnd, WM_USER+1, 1, (LPARAM)this);
}

void ChildWindow::destroyExtra()
{
	SendMessage(parent->Hwnd, WM_USER + 1, 0, (LPARAM)this);
}






void ChildWindow::SetText(const wstring& Text)
{

	if (!Hwnd || !parent->Hwnd) return;	//if the window handler or parent window does not exist return.
	text = Text;

	SetWindowTextW(Hwnd, text.c_str());
	
}

void ChildWindow::SetText(wstring&& Text)
{

		//if the window handler or parent window does not exist return.
		if (!Hwnd || !parent->Hwnd) return;
		

		text = std::move(Text);
		//RECT rtc{ x,y,x + width,y + height };
		//RedrawWindow(Hwnd, &rtc, 0, RDW_ERASE);
		
		SetWindowTextW(Hwnd, text.c_str());
		
}




void ChildWindow::addimage(image& img)
{
	if (!parent->Hwnd || style == (style|SS_BITMAP)) return;
	
	style = style | SS_BITMAP;
	this->img = &img;
	SetWindowLongPtr(Hwnd, GWL_STYLE, style);
	SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);
	SendMessageW(Hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img.BM);
}





void ChildWindow::Move(int DX, int DY)
{

	x += DX; y += DY;
	SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);


}

void ChildWindow::E_set(const wstring& Text, int x, int y, int width, int height, ExtraWindow* parent)
{
	if (!parent) return;
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	text = Text;
	
	placeExtra();
}

void ChildWindow::E_set(wstring&& Text, int x, int y, int width, int height, ExtraWindow* parent)
{
	if (!parent) return;
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	text = std::move(Text);


	placeExtra();

}





void ChildWindow::E_Destroy()
{
	destroyExtra();
	
}

void ChildWindow::resize(int width, int height)
{
	this->width = width;
	this->height = height;
	SetWindowPos(Hwnd, 0, x, y, width, height, 0);
}

void ChildWindow::Remove()
{
	DestroyWindow(Hwnd);

	
}

void ChildWindow::AddBorder()
{
	style = style | WS_BORDER;
	if (!Hwnd) return;
	SetWindowLongPtr(Hwnd, GWL_STYLE, style);
	SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);
	
}




void ChildWindow::RemoveBorder()
{
	style = style & ~ES_AUTOHSCROLL;
	if (!Hwnd) return;
	SetWindowLongPtr(Hwnd, GWL_STYLE, style);
	SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);
}

void ChildWindow::Reposition(int x, int y)
{
	

	this->x = x;
	this->y = y;
	
	SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);

	

}

const wstring& ChildWindow::GetText() const
{
	return text;
}


void ChildWindow::set(const wstring& Text, int x, int y, int width, int height, MainWindow* parent)
{
	if (!parent) return;
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	text = Text;




	placeExtra();
}

void ChildWindow::set(wstring&& Text, int x, int y, int width, int height, MainWindow* parent)
{
	if (!parent) return;
	this->parent = parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	text = std::move(Text);

	placeExtra();
	
}






