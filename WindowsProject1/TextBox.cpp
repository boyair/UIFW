#include "TextBox.h"

void TextBox::place()
{
	if (!parent) return;




	if (edit)
	{
		Box = CreateWindowW(L"edit", text, style, x, y, width, height, parent, NULL, NULL, NULL);
		return;
	}
	Box = CreateWindowW(L"static", text, style, x, y, width, height, parent, NULL, NULL, NULL);
}

void TextBox::UpdateText()
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



TextBox::TextBox(bool edit):ChildWindow(),edit(edit)
{
	text = new wchar_t[textlength + 1];
}

TextBox::TextBox(const wchar_t* Text, int x, int y, int width, int height, bool edit,HWND* parent)
		:ChildWindow( Text,  x,  y,  width,  height,  parent),edit(edit)
{
	if (!parent) return;
	text = new wchar_t[textlength + 1];
	wcscpy_s(text,textlength,Text);
	
	

	if (edit)
	{
		Box = CreateWindowW(L"edit", Text, style  , x, y, width, height, *parent, NULL, NULL, NULL);
		return;
	}
	Box = CreateWindowW(L"static", Text, style, x, y, width, height, *parent, NULL, NULL, NULL);
}

void TextBox::set(const wchar_t* Text, int x, int y, int width, int height, HWND* parent)
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

	

	if (edit)
	{
		Box = CreateWindowW(L"edit", Text, style, x, y, width, height, *parent, NULL, NULL, NULL);
		return;
	}
	Box = CreateWindowW(L"static", Text, style, x, y, width, height, *parent, NULL, NULL, NULL);



}

std::wstring TextBox::GetText()
{
	
	   GetWindowText(Box, text, textlength);
	   return (std::wstring)text;
}

void TextBox::Move(int DX, int DY)
{
	if (edit) UpdateText();
	ChildWindow::Move(DX, DY);
	
}

void TextBox::Reposition(int x, int y)
{
	if (edit) UpdateText();
	ChildWindow::Reposition(x, y);
}

void TextBox::ChangeMaxCharacters(unsigned int NewMax)
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

void TextBox::addimage(const wchar_t* name)
{
	if (!parent) return;
	std::wstring fullname = std::wstring(name) + std::wstring(L".bmp");
	HBITMAP image = (HBITMAP)LoadImageW(NULL, fullname.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	DestroyWindow(Box);
	style = style | SS_BITMAP;
	Box = CreateWindowW(L"static", text, style, x, y, width, height, parent, NULL, NULL, NULL);
	SendMessageW(Box, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);

}



void TextBox::AddHorizontalScrolling()
{ 
	if (!edit) return;
	GetWindowText(Box, text, textlength);
	DestroyWindow(Box);

	style = style | ES_AUTOHSCROLL;
	place();
}

void TextBox::AddBorder()
{
	
	if (style == (style | WS_BORDER)) return;
	UpdateText();
	DestroyWindow(Box);
	style = style | WS_BORDER;
	place();
}


void TextBox::AddVerticalScrolling()
{
	
	if (!edit) return;
	if (style == (style | ES_AUTOVSCROLL | ES_MULTILINE)) return;
	GetWindowText(Box, text, textlength);
	DestroyWindow(Box);
	style = style| ES_AUTOVSCROLL| ES_MULTILINE;
	place();

}

void TextBox::RemoveVerticalScrolling()
{
	if (!edit) return;
	if (style ==( style & ~ES_AUTOVSCROLL & ~ES_MULTILINE)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~ES_AUTOVSCROLL & ~ES_MULTILINE;
	place();
}

void TextBox::RemoveHorizontalScrolling()
{
	if (!edit) return;
	if (style == (style & ~ES_AUTOHSCROLL)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~ES_AUTOHSCROLL;
	place();
}

void TextBox::RemoveBorder()
{
	if (style == (style & ~ES_AUTOHSCROLL)) return;
	GetWindowText(Box, text, width / 8 + 1);
	DestroyWindow(Box);
	style = style & ~ES_AUTOHSCROLL;
	place();
}



TextBox::~TextBox()
{
	delete[] text;
	DestroyWindow(Box);

}

