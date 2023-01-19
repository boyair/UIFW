#include "wstring.h"
namespace UIFW {
	wstring::wstring() {}

	wstring::wstring(const wchar_t* str)
	{
		if (!str) return;
		size_t strlen = wcslen(str);
		if (!(strlen < BufferSize))
		{
			size = strlen + 1;
			this->str = new wchar_t[size];
		}

		wcscpy_s(this->str, strlen + 1, str);
	}

	const wchar_t* wstring::c_str() const
	{
		return str;
	}

	wchar_t* wstring::c_str()
	{
		return str;
	}

	wstring::wstring(const wstring& other)
	{


		if (other.str != other.SmallBuffer)
		{
			size = other.size;
			str = new wchar_t[size];
		}
		wcscpy_s(str, getsize(), other.str);
	}


	wstring::wstring(wstring&& other) noexcept
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
		other.str = other.SmallBuffer;
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
		if (other.size < getsize())
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

	bool wstring::operator==(const wstring& other) const
	{
		return !wcscmp(str, other.str);
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

	wstring wstring::operator+(const wstring& other) const
	{
		wstring result = *this;
		size_t newsize = getlength() + other.getlength() + 1;
		result.resize(newsize);
		wchar_t* cont = result.str + getlength();

		memcpy(cont, other.c_str(), (wcslen(other.c_str()) + 1) * sizeof(wchar_t));
		return result;
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

	void wstring::resize(size_t newsize)
	{

		wchar_t* save = str;
		if (newsize < getsize())save[newsize - 1] = 0;
		//handeling resize in SmallBuffer

		if (newsize < BufferSize)
		{
			if (str == SmallBuffer)
				return;

			str = SmallBuffer;
			if (save)
			{
				save[newsize] = 0;
				wcscpy_s(str, BufferSize, save);
				delete[] save;
			}
			return;
		}

		if (newsize < getsize())
			save[newsize - 1] = 0;
		str = new wchar_t[newsize];
		wcscpy_s(str, newsize, save);
		size = newsize;
		//deletes str if wasnt in smallbuffer

		if (save != SmallBuffer)
			delete[] save;

	}

	void wstring::operator+=(const wstring& other)
	{
		size_t newsize = getlength() + other.getlength() + 1;
		resize(newsize);
		wchar_t* cont = str + getlength();

		memcpy(cont, other.c_str(), (wcslen(other.c_str()) + 1) * sizeof(wchar_t));
		// str[newsize - 1] = 0;


	}

	size_t wstring::getlength() const
	{
		return wcslen(str);
	}

	size_t wstring::getsize() const
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
}