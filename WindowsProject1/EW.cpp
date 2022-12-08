#include "EW.h"

void EW::place()
{
	if (parent) 
	Box = CreateWindowW(L"edit", text.c_str(), style, x, y, width, height, parent, NULL, NULL, NULL);
}

void EW::UpdateText()
{
	
	text.resize(GetWindowTextLengthW(Box)+1);

	
	GetWindowTextW(Box,text.c_str(), (int)text.getsize());
	


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
	
	
	style = style | ES_AUTOHSCROLL;
	if (!Box) return;
	UpdateText();
	DestroyWindow(Box);
	place();
}

void EW::AddBorder()
{
	
	style = style | Border;
	if (!Box) return;
	UpdateText();
	DestroyWindow(Box);
	place();
}


void EW::AddVerticalScrolling()
{
	
	
	style = style| Vscroll;
	if (!Box) return;
	UpdateText();
	DestroyWindow(Box);
	place();

}

void EW::RemoveVerticalScrolling()
{
	
	style = style & ~Vscroll;
	if (!Box) return;
	UpdateText();
	DestroyWindow(Box);
	place();
}

void EW::RemoveHorizontalScrolling()
{
	
	style = style & ~Hscroll;
	if (!Box) return;
	UpdateText();
	DestroyWindow(Box);
	place();
}

void EW::RemoveBorder()
{
	style = style & ~Border;
	if (!Box) return;	UpdateText();
	DestroyWindow(Box);
	place();
}



EW::~EW()
{	DestroyWindow(Box);

}

