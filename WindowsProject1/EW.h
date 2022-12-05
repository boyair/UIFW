#pragma once
#include "ChildWindow.h"
#include<math.h>
#define Hscroll 0x0080L
#define Vscroll 0x0044L
class EW:public ChildWindow
{
	// basic functions used in a lot of style change functions.
	void place();
	void UpdateText();

public:

	//creators
	EW();
	EW(const wstring& Text,int x,int y,int width,int height, HWND* parent);
	EW(wstring&& Text, int x, int y, int width, int height, HWND* parent);


	//basic functionallity
	wstring GetText();
	void Move(int DX, int DY);
	void Reposition(int x, int y);
	void addimage(const wstring& name);
	//style change

	void AddVerticalScrolling();
	void AddHorizontalScrolling();
	void AddBorder();
	void RemoveVerticalScrolling();
	void RemoveHorizontalScrolling();
	void RemoveBorder();


	~EW();
};