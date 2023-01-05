#pragma once
#include "ChildWindow.h"
class Button: public ChildWindow
{
	long long id;
	void place() override;
	static long BTBKCLR, BTTXCLR;


public:
	
	Button(long long id);
	Button(const wstring& Text, int x, int y, int width, int height, long long id, MainWindow* parent) ;
	Button( wstring&& Text, int x, int y, int width, int height, long long id, MainWindow* parent) ;
	
//	void set(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);
	void addimage( image& img) override;
	~Button();


};

