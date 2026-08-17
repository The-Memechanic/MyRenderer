# Third-party notices

This project vendors the following MIT/public-domain libraries directly in
`vendor/`. Their original license headers are preserved at the top of each
file; this is just a summary.

- **tiny_gltf.h**, **json.hpp**, **stb_image_write.h**
  From https://github.com/syoyo/tinygltf (release branch, attic/), MIT licensed.
  json.hpp is nlohmann/json, also MIT licensed: https://github.com/nlohmann/json

- **stb_image.h** (v2.28)
  From https://github.com/nothings/stb, public domain / MIT (dual-licensed,
  your choice).

- **GLFW**, **GLM**
  Fetched automatically via CMake FetchContent from their respective repos;
  zlib/MIT and MIT licensed respectively.

- **GLAD**
  Generated per-project via https://gen.glad.sh; the generated loader code
  itself is public domain (CC0) / MIT depending on generator settings — the
  Khronos API headers it wraps are under the Apache 2.0 license.
