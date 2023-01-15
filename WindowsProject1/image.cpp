#include "image.h"

namespace UIFW {
	image::image(wstring&& name) :BM(NULL), width(0), height(0)
	{
		LoadFromFile(std::move(name));

	}

	image::image(const wstring& name) :BM(NULL), width(0), height(0)
	{
		LoadFromFile(name);

	}
	image::image(wstring&& name, int width, int height) :BM(NULL), width(width), height(height)
	{
		LoadFromFile(name, width, height);
	}
	image::image(const wstring& name, int width, int height) :BM(NULL), width(width), height(height)
	{
		LoadFromFile(name, width, height);
	}
	image::image() :BM(NULL), width(0), height(0)
	{
	}

	bool image::LoadFromFile(wstring&& name, int width, int height)
	{

		//set the name
		this->name = std::move(name);
		if (this->name[this->name.getlength() - 4] != L'.')
			this->name += (wstring)L".bmp";

		//loads the image and sets parameters

		BM = (HBITMAP)LoadImageW(NULL, this->name.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
		if (!BM)return false;		//returns false if image load failed
		this->width = width;
		this->height = height;
		return true;
	}

	bool image::LoadFromFile(const wstring& name, int width, int height)
	{

		//set the name
		this->name = name;
		if (this->name[this->name.getlength() - 4] != L'.')
			this->name += (wstring)L".bmp";

		//loads the image and sets parameters

		BM = (HBITMAP)LoadImageW(NULL, this->name.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
		if (!BM)return false;		//returns false if image load failed
		this->width = width;
		this->height = height;
		return true;
	}

	image::~image()
	{
		if (BM) DeleteObject(BM);

	}

	bool image::ConatainsImage()
	{
		return BM;
	}

	bool image::LoadFromFile(wstring&& name)
	{

		//set the name
		this->name = std::move(name);
		if (this->name[this->name.getlength() - 4] != L'.')
			this->name += (wstring)L".bmp";

		//loads the image and sets parameters

		BM = (HBITMAP)LoadImageW(NULL, this->name.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		if (!BM)return false;		//returns false if image load failed
		BITMAP temp;
		GetObject(BM, sizeof(BITMAP), &temp);
		width = temp.bmWidth;
		height = temp.bmHeight;
		return true;
	}

	bool image::LoadFromFile(const wstring& name)
	{

		//set the name
		this->name = name;
		if (this->name[this->name.getlength() - 4] != L'.')
			this->name += (wstring)L".bmp";

		//loads the image and sets parameters

		BM = (HBITMAP)LoadImageW(NULL, this->name.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		if (!BM)return false;		//returns false if image load failed
		BITMAP temp;
		GetObject(BM, sizeof(BITMAP), &temp);
		width = temp.bmWidth;
		height = temp.bmHeight;
		return true;
	}
}