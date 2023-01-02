#pragma once
#include<Windows.h>
#include "image.h"
#include "wstring.h"
#include "ExtraWindow.h"

#define Border 0x00800000L

class ChildWindow:public Window
{
	friend class ExtraWindow;
protected:
	MainWindow* parent;
	image* img;
	
	
	virtual void place();
	virtual void placeExtra();
	virtual void destroyExtra();
	


public:
	
	
	ChildWindow(); 
	//LRESULT CALLBACK  ColorProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
	
	ChildWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
	ChildWindow( wstring&& Text, int x, int y, int width, int height, MainWindow* parent);

	void SetText(const wstring& Text);
	void SetText(wstring&& Text);

	

	virtual void addimage(image& name) ;
	virtual void AddBorder();
	virtual void RemoveBorder();
	virtual void resize(int width, int height);
	virtual void Move(int DX, int DY);
	virtual void Reposition(int x,int y);
	        void set(const wstring& Text, int x, int y, int width, int height, MainWindow* parent);
			void set(wstring&& Text, int x, int y, int width, int height, MainWindow* parent);
			const wstring& GetText() const;
			void E_set(const wstring& Text, int x, int y, int width, int height, ExtraWindow* parent);
			void E_set(wstring&& Text, int x, int y, int width, int height, ExtraWindow* parent);
			void E_Destroy();



	


	

	//void set(wstring&& Text, int x, int y, int width, int height, ExtraWindow* parent);
	 
	void Remove();


};

