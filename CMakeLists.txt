cmake_minimum_required(VERSION 4.3)
project(MyRenderer CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------
include(FetchContent)

# GLFW - windowing / input / OpenGL context creation
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLM - header-only math library
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glm)

# GLAD - OpenGL function loader.
# GLAD is NOT fetched automatically because it must be generated for a
# specific GL version/profile. See vendor/glad/README.md for the one-time
# setup step. Once generated, it lives at vendor/glad/{include,src}.
add_library(glad STATIC vendor/glad/src/glad.c)
target_include_directories(glad PUBLIC vendor/glad/include)

# stb_image - single-header image loader (already vendored, see vendor/stb)
add_library(stb_image STATIC vendor/stb/stb_image.cpp)
target_include_directories(stb_image PUBLIC vendor/stb)

# tinygltf - single-header glTF 2.0 loader (already vendored, see vendor/tinygltf)
add_library(tinygltf STATIC vendor/tinygltf/tinygltf_impl.cpp)
target_include_directories(tinygltf PUBLIC vendor/tinygltf)
target_link_libraries(tinygltf PUBLIC stb_image)

# -----------------------------------------------------------------------------
# Main executable
# -----------------------------------------------------------------------------
file(GLOB_RECURSE MY_RENDERER_SOURCES CONFIGURE_DEPENDS
        src/*.cpp
        src/*.h
)

add_executable(MyRenderer ${MY_RENDERER_SOURCES}
        src/render/Mesh.cpp
        src/render/Mesh.h
        src/core/Application.cpp
        src/core/Application.h
        src/scene/Transform.cpp
        src/scene/Transform.h
        src/scene/Camera.cpp
        src/scene/Camera.h
        src/render/Texture.cpp
        src/render/Texture.h
        src/scene/Light.h
        src/scene/PointLight.cpp
        src/scene/PointLight.h)

target_include_directories(MyRenderer PRIVATE src)

target_link_libraries(MyRenderer PRIVATE
        glfw
        glad
        glm::glm
        stb_image
        tinygltf
)

if (WIN32)
    target_link_libraries(MyRenderer PRIVATE opengl32)
elseif (APPLE)
    target_link_libraries(MyRenderer PRIVATE "-framework OpenGL")
elseif (UNIX)
    target_link_libraries(MyRenderer PRIVATE GL)
endif ()

# -----------------------------------------------------------------------------
# Copy assets (shaders, models, textures) next to the built executable so
# relative paths in the code resolve correctly when run from CLion.
# -----------------------------------------------------------------------------
# Track all asset files so changes to them trigger a rebuild/copy
file(GLOB_RECURSE ASSET_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/assets/*)

add_custom_target(CopyAssets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:MyRenderer>/assets
        DEPENDS ${ASSET_FILES}
        COMMENT "Copying assets to build output"
)

add_dependencies(MyRenderer CopyAssets)