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
		:ChildWindow( Text,  x,  y,  width,  height,  parent){	}



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
	memcpy(text, save, (min(NewMax, textlength)+1) * sizeof(wchar_t));
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
	
	if (style == (style | Border)) return;
	UpdateText();
	DestroyWindow(Box);
	style = style | Border;
	place();
}


void EW::AddVerticalScrolling()
{
	
	
	if (style == (style | Vscroll)) return;
	GetWindowText(Box, text, textlength);
	DestroyWindow(Box);
	style = style| Vscroll;
	place();

}

void EW::RemoveVerticalScrolling()
{
	
	if (style ==( style & ~Vscroll)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~Vscroll;
	place();
}

void EW::RemoveHorizontalScrolling()
{
	
	if (style == (style & ~Hscroll)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~Hscroll;
	place();
}

void EW::RemoveBorder()
{
	if (style == (style & ~Border)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~Border;
	place();
}



EW::~EW()
{
	delete[] text;
	DestroyWindow(Box);

}

