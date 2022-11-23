#pragma once
#include "ChildWindow.h"
#include<math.h>
class EW:public ChildWindow
{
	// basic functions used in a lot of style change functions.
	void place();
	void UpdateText();

public:

	//creators
	EW();
	EW(const wchar_t* Text,int x,int y,int width,int height, HWND* parent);
	void set(const wchar_t* Text, int x, int y, int width, int height, HWND* parent);


	//basic functionallity
	std::wstring GetText();
	void Move(int DX, int DY);
	void Reposition(int x, int y);
	void ChangeMaxCharacters(unsigned int NewMax);
	void addimage(const wchar_t* name);
	//style change

	void AddVerticalScrolling();
	void AddHorizontalScrolling();
	void AddBorder();
	void RemoveVerticalScrolling();
	void RemoveHorizontalScrolling();
	void RemoveBorder();


	~EW();
};