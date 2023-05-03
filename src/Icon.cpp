#include <rlIcon/Icon.hpp>

// Win32
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>


namespace rlIcon
{

	namespace
	{
		// Source: "The format of icon resources" by Raymond Chen:
		// https://devblogs.microsoft.com/oldnewthing/20120720-00/?p=7083

		struct GRPICONDIRENTRY
		{
			BYTE  bWidth;
			BYTE  bHeight;
			BYTE  bColorCount;
			BYTE  bReserved;
			WORD  wPlanes;
			WORD  wBitCount;
			DWORD dwBytesInRes;
			WORD  nId;
		};
		struct GRPICONDIR
		{
			WORD idReserved;
			WORD idType; // Resource type (1 for icons).
			WORD idCount;
			GRPICONDIRENTRY idEntries;
		};
	}

	

	Icon::~Icon() { clear(); }
	
	bool Icon::loadFromResource(HMODULE hModule, WORD iID)
	{
		clear();

		HRSRC hRSRC = FindResource(hModule, MAKEINTRESOURCE(iID), RT_GROUP_ICON);
		if (hRSRC == NULL)
			return false;

		HGLOBAL hGlobal = LoadResource(hModule, hRSRC);
		if (hGlobal == NULL)
			return false;

		auto pDir = (GRPICONDIR*)LockResource(hGlobal);
		if (pDir == NULL)
			return false;

		if (pDir->idType != 1)
			return false;

		m_oSubImages.reserve(pDir->idCount);
		GRPICONDIRENTRY *pEntry = &pDir->idEntries;
		for (size_t i = 0; i < pDir->idCount; ++i)
		{
			// TODO:
			// https://stackoverflow.com/questions/20729156/find-out-number-of-icons-in-an-icon-resource-using-win32-api
			// https://devblogs.microsoft.com/oldnewthing/20120720-00/?p=7083
			SubImage si{};

			++pEntry;
		}

		return true;
	}

	void Icon::clear()
	{
		for (auto &o : m_oSubImages)
		{
			CloseHandle(o.hIcon);
		}
		m_oSubImages.clear();
	}

}
