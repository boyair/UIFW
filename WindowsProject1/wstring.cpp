#include "wstring.h"

wstring::wstring() :str(SmallBuffer), SmallBuffer{ 0 } {}

wstring::wstring(const wchar_t* str) : str(SmallBuffer), SmallBuffer{ 0 }
{
	size_t strlen = wcslen(str);
	if (!(strlen < BufferSize))
	{
		size = strlen + 1;
		this->str = new wchar_t[size];
	}

	wcscpy_s(this->str, strlen + 1, str);
}

wchar_t* wstring::c_str() const
{
	return str;
}

wstring::wstring(const wstring& other) :str(SmallBuffer), SmallBuffer{ 0 }
{
	if (other.str != other.SmallBuffer)
	{
		size = other.size;
		str = new wchar_t[size];
	}
	wcscpy_s(str, getsize(), other.str);
}


wstring::wstring(wstring&& other) noexcept :str(SmallBuffer), SmallBuffer{ 0 }
{

	if (other.str == other.SmallBuffer)
	{
		wcscpy_s(SmallBuffer, BufferSize, other.SmallBuffer);
	}
	else
	{
		size = other.size;
		str = other.str;
	}
	other.size = 0;
	other.str = nullptr;
	memset(other.SmallBuffer, 0, sizeof(other.SmallBuffer));

}


void wstring::operator =(const wstring& other)
{
	//if no other is Null reset values.
	if (!&other || !other.str)
	{
		str = nullptr;
		memset(SmallBuffer, 0, sizeof(SmallBuffer));
		return;
	}

	//handeling copy to SmallBuffer

	if (other.str == other.SmallBuffer)
	{
		if (str != SmallBuffer)
		{
			delete[] str;
			str = SmallBuffer;
		}
		wcscpy_s(str, BufferSize, other.str);
		return;
	}


	//copy smaller string to already allocated buffer
	if (other.size <= getsize())
	{
		size = other.size;
		wcscpy_s(str, size, other.str);
		return;
	}
	//deletes str if wasnt in smallbuffer
	if (str != SmallBuffer)
		delete[] str;

	size = other.size;
	str = new wchar_t[size];
	wcscpy_s(str, size, other.str);
}


void wstring::operator = (const wchar_t* str)
{
	if (!str) return;
	size_t strlen = wcslen(str);

	if (strlen < BufferSize)
	{
		if (this->str != SmallBuffer)
		{
			delete[] this->str;
			this->str = SmallBuffer;
		}

		wcscpy_s(this->str, BufferSize, str);
		return;

	}


	if (strlen <= getsize())
	{
		size = strlen + 1;
		wcscpy_s(this->str, size, str);
		return;
	}

	if (this->str != SmallBuffer)
		delete[] this->str;

	size = strlen + 1;
	this->str = new wchar_t[size];
	wcscpy_s(this->str, size, str);

}

wstring& wstring::operator=(wstring&& other)noexcept
{
	//if no other is Null reset values.
	if (!&other || !other.str)
	{
		str = nullptr;
		memset(SmallBuffer, 0, sizeof(SmallBuffer));
		return *this;
	}

	//handeling copy to SmallBuffer

	if (other.str == other.SmallBuffer)
	{
		if (str != SmallBuffer)
		{
			delete[] str;
			str = SmallBuffer;
		}
		wcscpy_s(str, BufferSize, other.str);
		return *this;
	}


	


	//deletes str if wasnt in smallbuffer
	if (str != SmallBuffer)
		delete[] str;

	//moving pointer
	size = other.size;
	str = other.str;

	//reseting old pointer.
	other.size = 0;
	other.str = nullptr;
	memset(other.SmallBuffer, 0, sizeof(other.SmallBuffer));

	return *this;


}

wchar_t& wstring::operator[](size_t index)
{
#ifdef _DEBUG 


	if (index > getsize() - 2)
	{
		return *((wchar_t*)(nullptr));
	}
#endif // DEBUG
	return str[index];
}

void wstring::resize(unsigned int newsize)
{

	wchar_t* save = str;

	//handeling resize in SmallBuffer

	if (newsize < BufferSize)
	{
		if (str == SmallBuffer)
			return;

		str = SmallBuffer;
		save[newsize] = 0;
		wcscpy_s(str, BufferSize, save);
		delete[] save;
		return;
	}


	str = new wchar_t[newsize];
	save[newsize - 1] = 0;
	wcscpy_s(str, newsize, save);
	size = newsize;
	//deletes str if wasnt in smallbuffer

	if (save != SmallBuffer)
		delete[] save;

}

void wstring::operator+=(const wstring& other)
{
	unsigned int newsize = getlength() + other.getlength() + 1;
	resize(newsize);
	wchar_t* cont = str + getlength();
	cont[4] = 0;
	wcscpy_s(cont, newsize,other.c_str());
	

}

size_t wstring::getlength() const
{
	return wcslen(str);
}

unsigned int wstring::getsize() const
{
	if (str == SmallBuffer)
		return BufferSize;
	return (unsigned int)size;

}

wstring::~wstring()
{
	if (str != SmallBuffer)
		delete[] str;
}
