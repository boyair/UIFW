#include "Menu.h"

HMENU Menu::hmenu = CreateMenu();
Menu::Menu(HWND* parentWindow, const std::string& name,long id,bool parent):parentWindow(*parentWindow),name(name),id(id), parent(parent)
{
	
	std::wstring widestr = std::wstring(name.begin(), name.end());
	const wchar_t* widecstr = widestr.c_str();
	if (parent)
	{
		child = CreateMenu();
		AppendMenu(hmenu, MF_POPUP, (UINT_PTR)child, widecstr);
	}
	else
	AppendMenu(hmenu, MF_STRING, id, widecstr);

	if (parentWindow != NULL)
	SetMenu(*parentWindow, hmenu);

}
bool Menu::AddSubMenu(const std::string& name, long id)
{
	if (!parent) return false;
	std::wstring widestr = std::wstring(name.begin(), name.end());
	const wchar_t* widecstr = widestr.c_str();
	AppendMenu(child, MF_STRING , id, widecstr);
	return true;

}

void Menu::destroy()
{
	DestroyMenu(hmenu);
}
