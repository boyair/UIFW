#include "EW.h"

void EW::place()
{
	if (parent) 
	Box = CreateWindowW(L"edit", text, style, x, y, width, height, parent, NULL, NULL, NULL);
}

void EW::UpdateText()
{
	
	const unsigned int newsize = GetWindowTextLengthW(Box);
	if (newsize > textlength)
	{
		wchar_t* save = text;
		text = new wchar_t[newsize + 1];
		delete[] save;
		textlength = newsize;
	}
	GetWindowTextW(Box,text,newsize+1);
	text[newsize] = '\0';


}



EW::EW():ChildWindow()
{
	text = new wchar_t[textlength + 1];
}

EW::EW(const wchar_t* Text, int x, int y, int width, int height,HWND* parent)
		:ChildWindow( Text,  x,  y,  width,  height,  parent)
{
	if (!parent) return;
	text = new wchar_t[textlength + 1];
	wcscpy_s(text,textlength,Text);
	
	

	
		Box = CreateWindowW(L"edit", Text, style  , x, y, width, height, *parent, NULL, NULL, NULL);
	
}

void EW::set(const wchar_t* Text, int x, int y, int width, int height, HWND* parent)
{
	if (!parent) return;
	this->parent = *parent;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	
	const unsigned int newsize = wcsnlen_s(Text, 0xFFFFFF);
	if (newsize > textlength)
	{
		wchar_t* save = text;
		text = new wchar_t[newsize + 1];
		delete[] save;
		textlength = newsize;
	}
	wcscpy_s(text,textlength+1,  Text);

	

	
		Box = CreateWindowW(L"edit", Text, style, x, y, width, height, *parent, NULL, NULL, NULL);
	



}

std::wstring EW::GetText()
{
	
	   GetWindowText(Box, text, textlength);
	   return (std::wstring)text;
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

void EW::ChangeMaxCharacters(unsigned int NewMax)
{

	GetWindowText(Box, text, textlength);
	int lower = min(textlength, NewMax);
	wchar_t* save = text;
	text = new wchar_t[NewMax + 1];
	memcpy(text, save, min(NewMax, textlength) * sizeof(wchar_t)+1);
	text[NewMax] = '\0';
	delete[] save;
	SetWindowText(Box, text);
	textlength = NewMax;

}

void EW::addimage(const wchar_t* name)
{
	//might add a debug break

}




void EW::AddHorizontalScrolling()
{ 
	
	GetWindowText(Box, text, textlength);
	DestroyWindow(Box);

	style = style | ES_AUTOHSCROLL;
	place();
}

void EW::AddBorder()
{
	
	if (style == (style | WS_BORDER)) return;
	UpdateText();
	DestroyWindow(Box);
	style = style | WS_BORDER;
	place();
}


void EW::AddVerticalScrolling()
{
	
	
	if (style == (style | ES_AUTOVSCROLL | ES_MULTILINE)) return;
	GetWindowText(Box, text, textlength);
	DestroyWindow(Box);
	style = style| ES_AUTOVSCROLL| ES_MULTILINE;
	place();

}

void EW::RemoveVerticalScrolling()
{
	
	if (style ==( style & ~ES_AUTOVSCROLL & ~ES_MULTILINE)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~ES_AUTOVSCROLL & ~ES_MULTILINE;
	place();
}

void EW::RemoveHorizontalScrolling()
{
	
	if (style == (style & ~ES_AUTOHSCROLL)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~ES_AUTOHSCROLL;
	place();
}

void EW::RemoveBorder()
{
	if (style == (style & ~ES_AUTOHSCROLL)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~ES_AUTOHSCROLL;
	place();
}



EW::~EW()
{
	delete[] text;
	DestroyWindow(Box);

}

