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

#pragma pack(push)
#pragma pack(2)
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
#pragma pack(pop)
	}

	

	Icon::Icon(const Icon &other)
	{
		m_oSubImages = other.m_oSubImages;

		for (auto &o : m_oSubImages)
		{
			o.hIcon = CopyIcon(o.hIcon);
		}
	}

	Icon::~Icon() { clear(); }

	Icon &Icon::operator=(const Icon &other)
	{
		if (this == &other)
			return *this;

		m_oSubImages = other.m_oSubImages;
		for (auto &o : m_oSubImages)
		{
			o.hIcon = CopyIcon(o.hIcon);
		}
		return *this;
	}
	
	bool Icon::loadFromResource(HMODULE hModule, WORD iID)
	{
		clear(); // delete previously loaded images

		if (hModule == NULL)
			return false;

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
			SubImage si =
			{
				.hIcon         = NULL,
				.iWidth        = pEntry->bWidth,
				.iHeight       = pEntry->bHeight,
				.iColorCount   = pEntry->bColorCount,
				.iColorPlanes  = pEntry->wPlanes,
				.iBitsPerPixel = pEntry->wBitCount
			};

			// load the icon data
			{
				const HRSRC hRSRC = FindResource(hModule, MAKEINTRESOURCE(pEntry->nId), RT_ICON);
				if (hRSRC == NULL)
					continue; // can't find icon
				const HGLOBAL hGlobal = LoadResource(hModule, hRSRC);
				if (hGlobal == NULL)
					continue; // can't load icon resource
				BYTE *pData  = (BYTE*)LockResource(hGlobal);
				if (pData == NULL)
					continue; // can't load icon data
				const DWORD dwSize = SizeofResource(hModule, hRSRC);

				si.hIcon = CreateIconFromResourceEx(pData, dwSize, TRUE, 0x00030000, 0, 0,
					LR_DEFAULTCOLOR);
				if (si.hIcon == NULL)
					continue; // failed to load icon
			}

			if (si.iWidth == 0 || si.iHeight == 0)
			{
				ICONINFO ii{};
				if (GetIconInfo(si.hIcon, &ii))
				{
					DeleteObject(ii.hbmMask);

					BITMAP bmp{};
					if (GetObject(ii.hbmColor, sizeof(bmp), &bmp))
					{
						si.iWidth  = bmp.bmWidth;
						si.iHeight = bmp.bmHeight;
					}

					DeleteObject(ii.hbmColor);
				}
			}

			m_oSubImages.push_back(std::move(si));

			++pEntry;
		}

		return true;
	}

	void Icon::clear()
	{
		for (auto &o : m_oSubImages)
		{
			DestroyIcon(o.hIcon);
		}
		m_oSubImages.clear();
	}

}
