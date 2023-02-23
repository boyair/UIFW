#include "EditWindow.h"
namespace UIFW {
	void EditWindow::place()
	{
		if (parent)
			Hwnd = CreateWindowW(L"edit", text.c_str(), style, x, y, width, height, parent->Hwnd, NULL, NULL, NULL);
	}

	void EditWindow::UpdateText()
	{

		text.resize((size_t)(GetWindowTextLengthW(Hwnd) + 1));


		GetWindowTextW(Hwnd, text.c_str(), (int)text.getsize());



	}

	EditWindow::EditWindow() :ChildWindow()
	{
	}

	EditWindow::EditWindow(const wstring& Text, int x, int y, int width, int height, MainWindow* parent)
	{
		text = Text;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->parent = parent;
		PlaceExtra();

	}

	EditWindow::EditWindow(wstring&& Text, int x, int y, int width, int height, MainWindow* parent)
	{
		text = std::move(Text);
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->parent = parent;
		PlaceExtra();
	}



	wstring EditWindow::GetText()
	{

		UpdateText();
		return text;
	}





	void EditWindow::AddHorizontalScrolling()
	{


		style = style | ES_AUTOHSCROLL;
		if (!Hwnd) return;
		UpdateText();
		DestroyExtra();
		PlaceExtra();
	}




	void EditWindow::AddVerticalScrolling()
	{


		style = style | Vscroll;
		if (!Hwnd) return;
		UpdateText();
		DestroyExtra();
		PlaceExtra();

	}

	void EditWindow::RemoveVerticalScrolling()
	{

		style = style & ~Vscroll;
		if (!Hwnd) return;
		UpdateText();
		DestroyExtra();
		PlaceExtra();
	}

	void EditWindow::RemoveHorizontalScrolling()
	{

		style = style & ~Hscroll;
		if (!Hwnd) return;
		UpdateText();
		DestroyExtra();
		PlaceExtra();
	}

	void EditWindow::SetStyle(unsigned long NewStyle)
	{
		style = NewStyle | WS_CHILD | WS_VISIBLE;
		if (!Hwnd) return;
		if ((NewStyle & (ES_READONLY | ES_PASSWORD | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL)) != 0)
		{
			UpdateText();
			DestroyExtra();
			PlaceExtra();
			return;
		}
		SetWindowLongPtr(Hwnd, GWL_STYLE, style);
		SetWindowPos(Hwnd, 0, x, y, width, height, SWP_FRAMECHANGED);
	}




	EditWindow::~EditWindow()
	{
		DestroyWindow(Hwnd);

	}

}