#pragma once
#include <functional>
#include <vector>
#include "Window.h"
namespace UIFW {
	class MainWindow : public Window
	{
		friend class ChildWindow;
		friend class EW;
		friend class Button;
		friend LRESULT CALLBACK NonStaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		std::vector<HMENU> ChildMenus;
		HMENU menu = CreateMenu();
		std::vector<std::pair<int, std::function<void()>>> functionallitys;
		unsigned char ChildColorText[3]{ 0,0,0 };
		unsigned char ChildColorBK[3]{ 255,255,255 };
		unsigned char EWColorText[3]{ 255,255,255 };
		unsigned char EWColorBK[3]{ 0,0,0 };
		WNDCLASSW CLS = { 0 };
		LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
		image img;
		//constructors

		MainWindow(const wstring& Text, int x, int y, int width, int height);
		MainWindow(wstring&& Text, int x, int y, int width, int height);
	public:
		MainWindow(const wstring& Text, int x, int y, int width, int height, const image& img);
		MainWindow(wstring&& Text, int x, int y, int width, int height, const image& img);
		MainWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B);
		MainWindow(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned char G, unsigned char B);

		POINT GetMousePos();
		void(*onexit)() = nullptr;
		//change colors of childwindows
		void SetColor_Child_Text(unsigned char R, unsigned  char G, unsigned  char B);
		void SetColor_Child_BK(unsigned char R, unsigned  char G, unsigned  char B);
		void SetColor_EW_Text(unsigned char R, unsigned  char G, unsigned  char B);
		void SetColor_EW_BK(unsigned char R, unsigned  char G, unsigned  char B);
		//menus
		void AddMenu(const wstring& name, long id, bool parent);
		bool AddSubMenu(const wstring& name, int menuindex, long id);
		void RemoveMenuBar();

		void start();
		void Destroy();
		bool AddFunc(int id, std::function<void()>);


	};

}