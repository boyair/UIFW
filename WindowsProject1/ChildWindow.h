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
	virtual void SendImageExtra();
	virtual void SetTextExtra();


public:
	
	
	ChildWindow(); 
	
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


	virtual void E_addimage(image& img);
	virtual void E_AddBorder();
	virtual void E_RemoveBorder();
	virtual void E_resize(int width, int height);
	virtual void E_Move(int DX, int DY);
	virtual void E_Reposition(int x, int y);
			void E_set(const wstring& Text, int x, int y, int width, int height, ExtraWindow* parent);
			void E_set(wstring&& Text, int x, int y, int width, int height, ExtraWindow* parent);
			void E_SetText(const wstring& Text);
			void E_SetText(wstring&& Text);
			void E_Destroy();


	

	const wstring& GetText() const;
	void setOnExtra(const wstring& Text, int x, int y, int width, int height, ExtraWindow* parent);
	//void set(wstring&& Text, int x, int y, int width, int height, ExtraWindow* parent);
	 
	void Remove();


};

