// NOTE: the classic header-only C++ tinygltf (tiny_gltf.h + json.hpp +
// stb_image_write.h) now lives on the "release" branch under attic/, since
// the main branch moved to a new v3 C API. These three files are already
// vendored in this folder.
//
// stb_image.h itself lives in vendor/stb/ (shared with the texture loader)
// and is implemented once in vendor/stb/stb_image.cpp. We tell tiny_gltf.h
// to skip its own bundled copy so we don't get duplicate symbol definitions.
#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_INCLUDE_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "stb_image.h"   // resolved via vendor/stb include dir, declarations only (impl is in stb_image.cpp)
#include "tiny_gltf.h"
