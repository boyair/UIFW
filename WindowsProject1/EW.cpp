#include "EW.h"

void EW::place()
{
	if (parent) 
	Box = CreateWindowW(L"edit", text.c_str(), style, x, y, width, height, parent, NULL, NULL, NULL);
}

void EW::UpdateText()
{
	
	text.resize(GetWindowTextLengthW(Box)+1);

	
	GetWindowTextW(Box,text.c_str(), text.getsize());
	


}

EW::EW():ChildWindow()
{
	
}

EW::EW(const wstring& Text, int x, int y, int width, int height,HWND* parent)
		:ChildWindow( Text,  x,  y,  width,  height,  parent){	}

EW::EW(wstring&& Text, int x, int y, int width, int height, HWND* parent)
	:ChildWindow((wstring&&) Text, x, y, width, height, parent)
{
}



wstring EW::GetText()
{
	
	   UpdateText();
	   return text;
}

void EW::Move(int DX, int DY)
{
	 UpdateText();
	ChildWindow::Move(DX, DY);
	
}

void EW::Reposition(int x, int y)
{
	 UpdateText();
	ChildWindow::Reposition(x, y);
}


void EW::addimage(const wstring& name)
{
	//might add a debug break

}




void EW::AddHorizontalScrolling()
{ 
	
	
	UpdateText();
	DestroyWindow(Box);
	style = style | ES_AUTOHSCROLL;
	place();
}

void EW::AddBorder()
{
	
	if (style == (style | Border)) return;
	UpdateText();
	DestroyWindow(Box);
	style = style | Border;
	place();
}


void EW::AddVerticalScrolling()
{
	
	
	if (style == (style | Vscroll)) return;
	UpdateText();
	DestroyWindow(Box);
	style = style| Vscroll;
	place();

}

void EW::RemoveVerticalScrolling()
{
	
	if (style ==( style & ~Vscroll)) return;
	UpdateText();
	DestroyWindow(Box);
	style = style & ~Vscroll;
	place();
}

void EW::RemoveHorizontalScrolling()
{
	
	if (style == (style & ~Hscroll)) return;
	UpdateText();
	DestroyWindow(Box);
	style = style & ~Hscroll;
	place();
}

void EW::RemoveBorder()
{
	if (style == (style & ~Border)) return;
	UpdateText();
	DestroyWindow(Box);
	style = style & ~Border;
	place();
}



EW::~EW()
{	DestroyWindow(Box);

}

