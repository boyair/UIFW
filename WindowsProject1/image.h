#pragma once
#include <Windows.h>
#include<string>
class image
{
	HBITMAP BM;
	std::wstring name;
	int width, height;

public:

	image();

	bool ConatainsImage();
	bool LoadFromFile(std::wstring name);


};

