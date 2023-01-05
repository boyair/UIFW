#pragma once
#include "ChildWindow.h"
#include<math.h>
#define Hscroll 0x0080L
#define Vscroll 0x0044L
class EW:public ChildWindow
{
	// basic functions used in a lot of style change functions.
	void place() override;
	void UpdateText();
	static long EWBKCLR, EWTXCLR;

public:

	//creators
	EW();
	EW(const wstring& Text,int x,int y,int width,int height, MainWindow* parent);
	EW(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);


	//basic functionallity
	wstring GetText();
	//style change

	void AddVerticalScrolling();
	void AddHorizontalScrolling();
	void RemoveVerticalScrolling();
	void RemoveHorizontalScrolling();
	


	~EW();
};