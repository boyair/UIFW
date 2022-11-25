#include "image.h"

image::image():BM(NULL),name(NULL)
{
}

bool image::LoadFromFile(std::wstring name)
{
	this->name = name;
	name += L".bmp";
	 BM = (HBITMAP)LoadImageW(NULL, name.c_str(), IMAGE_BITMAP, , , LR_LOADFROMFILE);

	//style = style | SS_BITMAP;
	//Box = CreateWindowW(L"static", text, style, x, y, width, height, parent, NULL, NULL, NULL);
	//SendMessageW(Box, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)image);
	return false;
}
