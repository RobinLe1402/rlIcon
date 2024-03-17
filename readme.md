# The rlIcon static library

This repo contains the static library `rlIcon` which loads all the subicons in an icon.


## Example Code
```
#include <rlIcon/Icon.hpp>

// [...]

WNDCLASSEXW wc = { sizeof(wc) };

// [...]

rlIcon::Icon oIcon;
if (oIcon.loadFromResource(GetModuleHandle(NULL), MAKEINTRESOURCEW(IDI_TESTICON)))
{
	wc.hIcon   = oIcon.getBigIcon();
	wc.hIconSm = oIcon.getSmallIcon();
}

// [...]
```


## Requirements

| Category              | Value                     |
|-----------------------|---------------------------|
| Target Platform       | Windows 10+ x64           |
| C++ Language Standard | ISO C++20                 |
| VS Platform Toolset   | Visual Studio 2022 (v143) |