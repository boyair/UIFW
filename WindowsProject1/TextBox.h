#pragma once
#include "ChildWindow.h"
#include<math.h>
class TextBox:public ChildWindow
{
	const bool edit;

	void place();
	void UpdateText();

public:

	//creators
	TextBox(bool edit);
	TextBox(const wchar_t* Text,int x,int y,int width,int height,bool edit, HWND* parent);
	void set(const wchar_t* Text, int x, int y, int width, int height, HWND* parent);


	//basic functionallity
	std::wstring GetText();
	void Move(int DX, int DY);
	void ChangeMaxCharacters(unsigned int NewMax);
	//style change

	void AddVerticalScrolling();
	void AddHorizontalScrolling();
	void AddBorder();
	void RemoveVerticalScrolling();
	void RemoveHorizontalScrolling();
	void RemoveBorder();


	~TextBox();
};