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

	/// <summary>
	/// A multisize icon loaded from a resource.
	/// </summary>
	class Icon final
	{
	public: // types

		/// <summary>
		/// A single image that is part of a multi-size icon.
		/// </summary>
		struct SubImage
		{
			/// <summary>
			/// A handle to the icon data.<para />
			/// Only valid as long as the <c>HMODULE</c> parameter of the <c>loadFromResource</c>
			/// function is valid.
			/// </summary>
			HICON hIcon;

			unsigned iWidth;     // Width, in pixels, of the image.
			unsigned iHeight;    // Height, in pixels, of the image.
			BYTE  iColorCount;   // Number of colors in image (0 if >= 8bpp).
			WORD  iColorPlanes;  // Color Planes.
			WORD  iBitsPerPixel; // Bits per pixel.
		};

		using iterator         = std::vector<SubImage>::const_iterator;
		using reverse_iterator = std::vector<SubImage>::const_reverse_iterator;


	public: // methods

		Icon()             = default;
		Icon(Icon &&)      = default;
		Icon(const Icon &other);
		~Icon();

		Icon &operator=(const Icon &other);
		Icon &operator=(Icon &&) = default;

		iterator begin() const { return m_oSubImages.begin(); }
		iterator end()   const { return m_oSubImages.end(); }
		reverse_iterator rbegin() const { return m_oSubImages.rbegin(); }
		reverse_iterator rend()   const { return m_oSubImages.rend(); }



		/// <summary>
		/// The count of images in the multisize icon.
		/// </summary>
		size_t count() const noexcept { return m_oSubImages.size(); }

		/// <summary>
		/// Get an image.
		/// </summary>
		const SubImage &operator[](size_t index) const { return m_oSubImages[index]; }



		/// <summary>
		/// Try to load a multisize icon from an icon resource.
		/// </summary>
		/// <param name="hModule">
		/// The module of the icon to load the icon from.<para />
		/// Cannot be <c>NULL</c>.<para />
		/// Must be valid as long as the <c>HICON</c> values are used.
		/// </param>
		/// <param name="iID">
		/// The ID of the icon to load.<para />
		/// Don't use any of the predefined <c>IDI_</c> values and
		/// don't apply the <c>MAKEINTRESOURCE</c> macro.
		/// </param>
		/// <returns>
		/// Could icon data be read? <para />
		/// Returns <c>TRUE</c> as soon as the data structure is valid,
		/// even if no icons have been loaded.
		/// </returns>
		bool loadFromResource(HMODULE hModule, WORD iID);

		/// <summary>
		/// Clear all data linked to this icon.<para />
		/// All the <c>HICON</c> values obtained from this object become invalid when calling this
		/// function.
		/// </summary>
		void clear();


	private: // variables
		
		std::vector<SubImage> m_oSubImages;

	};

}





#endif // RLICON_ICON