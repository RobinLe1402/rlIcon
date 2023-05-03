#pragma once
#ifndef RLICON_ICON
#define RLICON_ICON





// STL
#include <vector>

// Win32
#define WIN32_MEAN_AND_LEAN
#include <Windows.h>
#undef WIN32_MEAN_AND_LEAN



namespace rlIcon
{

	class Icon final
	{
	public: // types

		struct SubImage
		{
			HICON hIcon;

			BYTE  iWidth;        // Width, in pixels, of the image.
			BYTE  iHeight;       // Height, in pixels, of the image.
			BYTE  iColorCount;   // Number of colors in image (0 if >= 8bpp).
			WORD  iColorPlanes;  // Color Planes.
			WORD  iBitsPerPixel; // Bits per pixel.
		};

		using iterator         = std::vector<SubImage>::const_iterator;
		using reverse_iterator = std::vector<SubImage>::const_reverse_iterator;


	public: // methods

		Icon() = default;
		Icon(const Icon &) = default;
		Icon(Icon &&) = default;
		~Icon();

		Icon &operator=(const Icon &) = default;
		Icon &operator=(Icon &&) = default;

		iterator begin() const { return m_oSubImages.begin(); }
		iterator end()   const { return m_oSubImages.end(); }
		reverse_iterator rbegin() const { return m_oSubImages.rbegin(); }
		reverse_iterator rend()   const { return m_oSubImages.rend(); }



		size_t subImageCount() const noexcept { return m_oSubImages.size(); }
		const SubImage &operator[](size_t index) const { return m_oSubImages[index]; }



		bool loadFromResource(HMODULE hModule, WORD iID);
		void clear();


	private: // variables
		
		std::vector<SubImage> m_oSubImages;

	};

}





#endif // RLICON_ICON