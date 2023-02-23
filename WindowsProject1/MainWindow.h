#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include "Window.h"
namespace UIFW {
	class MainWindow : public Window
	{
	private:
		friend class ChildWindow;
		friend class EditWindow;
		friend class Button;
		friend LRESULT CALLBACK NonStaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		bool made = false;
		std::vector<HMENU> ChildMenus;
		HMENU menu = CreateMenu();
		unsigned char ChildColorText[3]{ 0,0,0 };
		unsigned char ChildColorBK[3]{ 255,255,255 };
		unsigned char EditWindowColorText[3]{ 255,255,255 };
		unsigned char EditWindowColorBK[3]{ 0,0,0 };
		WNDCLASSW CLS = { 0 };
		LRESULT CALLBACK  Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
		void UpdateRECT();
		image img;
		//constructors
		MainWindow(const wstring& Text, int x, int y, int width, int height);
		MainWindow(wstring&& Text, int x, int y, int width, int height);
		MainWindow(const MainWindow&) = delete;
	public:
		MainWindow();
		MainWindow(const wstring& Text, int x, int y, int width, int height, const image& img);
		MainWindow(wstring&& Text, int x, int y, int width, int height, const image& img);
		MainWindow(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B);
		MainWindow(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned char G, unsigned char B);

		void Init(const wstring& Text, int x, int y, int width, int height, const image& img);
		void Init(wstring&& Text, int x, int y, int width, int height, const image& img);
		void Init(const wstring& Text, int x, int y, int width, int height, unsigned char R, unsigned  char G, unsigned  char B);
		void Init(wstring&& Text, int x, int y, int width, int height, unsigned char R, unsigned char G, unsigned char B);

		POINT GetMousePos();


		std::function<void()> XButton = nullptr;
		std::function<void()> OnUpdate = nullptr;
		std::unordered_map <int, std::function<void()>> functionallitys;

		//change colors of childwindows
		void SetColor_Child_Text(unsigned char R, unsigned  char G, unsigned  char B);
		void SetColor_Child_BK(unsigned char R, unsigned  char G, unsigned  char B);
		void SetColor_EditWindow_Text(unsigned char R, unsigned  char G, unsigned  char B);
		void SetColor_EditWindow_BK(unsigned char R, unsigned  char G, unsigned  char B);
		//menus
		void AddMenu(const wstring& name, long id, bool parent);
		bool AddSubMenu(const wstring& name, int menuindex, long id);
		void RemoveMenuBar();
		void Start();
		void Destroy() override;

		RECT GetRECT() override;
		void Move(int DX, int DY) override;
		void Resize(int width, int height) override;
		void Reposition(int x, int y) override;
	//	bool AddFunc(int id, std::function<void()>);


	};

}