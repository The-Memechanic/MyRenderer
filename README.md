# MyRenderer

A graphics renderer built with C++ and OpenGL

## Roadmap / where to add things next

Class stubs were generated in `src/` — they're laid out to match this progression:

1. Window + OpenGL context (`core/Window`) - done
2. Shader compilation (`render/Shader`) - done
3. Mesh (`render/Mesh`) — hardcode a triangle/cube's VAO/VBO/EBO, draw it
   with `basic.vert`/`basic.frag` - done
4. Transform + MVP (`scene/Transform`) — get the cube rotating
5. Camera (`scene/Camera`) — WASD + mouse-look, perspective projection
6. Texture (`render/Texture`) — stb_image, UVs, sampling in the fragment shader
7. Phong lighting — normals + ambient/diffuse/specular in the fragment shader
8. Specular maps — `Material` struct with diffuse + specular textures
9. Multiple light types — `PointLight`, `DirectionalLight`, `SpotLight`
10. Model loading (`render/Model`) — tinygltf parsing into `Mesh` objects
11. Scene management (`scene/Scene`) — multiple `GameObject`s + lights
