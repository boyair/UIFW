#pragma once
#include <Windows.h>
#include <vector>
#include "wstring.h"
class Menu
{
	HWND& parentWindow;
	wstring name;
	const bool parent;
	HMENU child;
	static HMENU hmenu;
	 const long id;
public:
	Menu(HWND* parentWindow, const wstring& name, long id, bool parent);
	bool AddSubMenu(const wstring& name, long id);
	static void destroy();


};

