#include "EW.h"
namespace UIFW {
	void EW::place()
	{
		if (parent)
			Hwnd = CreateWindowW(L"edit", text.c_str(), style, x, y, width, height, parent->Hwnd, NULL, NULL, NULL);
	}

	void EW::UpdateText()
	{

		text.resize(GetWindowTextLengthW(Hwnd) + 1);


		GetWindowTextW(Hwnd, text.c_str(), (int)text.getsize());



	}

	EW::EW() :ChildWindow()
	{
	}

	EW::EW(const wstring& Text, int x, int y, int width, int height, MainWindow* parent)
	{
		text = Text;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->parent = parent;
		placeExtra();

	}

	EW::EW(wstring&& Text, int x, int y, int width, int height, MainWindow* parent)
	{
		text = std::move(Text);
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->parent = parent;
		placeExtra();
	}



	wstring EW::GetText()
	{

		UpdateText();
		return text;
	}





	void EW::AddHorizontalScrolling()
	{


		style = style | ES_AUTOHSCROLL;
		if (!Hwnd) return;
		UpdateText();
		destroyExtra();
		placeExtra();
	}




	void EW::AddVerticalScrolling()
	{


		style = style | Vscroll;
		if (!Hwnd) return;
		UpdateText();
		destroyExtra();
		placeExtra();

	}

	void EW::RemoveVerticalScrolling()
	{

		style = style & ~Vscroll;
		if (!Hwnd) return;
		UpdateText();
		destroyExtra();
		placeExtra();
	}

	void EW::RemoveHorizontalScrolling()
	{

		style = style & ~Hscroll;
		if (!Hwnd) return;
		UpdateText();
		destroyExtra();
		placeExtra();
	}




	EW::~EW()
	{
		DestroyWindow(Hwnd);

	}

}