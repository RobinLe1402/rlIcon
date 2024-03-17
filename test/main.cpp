#include <rlIcon/Icon.hpp>

#include "resource.h"

int main(int argc, char* argv[])
{
	rlIcon::Icon oIcon;

	if (!oIcon.loadFromResource(GetModuleHandle(NULL), MAKEINTRESOURCEW(IDI_RLCONSOLE)))
	{
		std::printf("Failed to load icons.\n");
		return 1;
	}
	std::printf("Successfully loaded %llu icons.\n", oIcon.count());
	for (size_t i = 0; i < oIcon.count(); ++i)
	{
		auto &o = oIcon[i];
		std::printf(
			"  Icon[%zu] =\n"
			"  {\n"
			"    Width:          %u\n"
			"    Height:         %u\n"
			"    Color Count:    %u\n"
			"    Color Planes:   %u\n"
			"    Bits Per Pixel: %u\n"
			"  };\n\n",
			i, o.iWidth, o.iHeight, o.iColorCount, o.iColorPlanes, o.iBitsPerPixel
		);
	}

	return 0;
}
