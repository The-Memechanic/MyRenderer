# MyRenderer

A graphics renderer built with C++ and OpenGL

## Roadmap / To-do list

1. Window + OpenGL context (`core/Window`) - done
2. Shader compilation (`render/Shader`) - done
3. Mesh (`render/Mesh`) — hardcode a triangle/cube's VAO/VBO/EBO, draw with `basic.vert`/`basic.frag` - done
4. Transform + MVP (`scene/Transform`) - done
5. Camera (`scene/Camera`) — movement controls, perspective projection - done
6. Texture (`render/Texture`) — stb_image, UVs, sampling in the fragment shader - done
7. Phong lighting — normals + ambient/diffuse/specular in the fragment shader
8. Specular maps — `Material` struct with diffuse + specular textures
9. Multiple light types — `PointLight`, `DirectionalLight`, `SpotLight`
10. Model loading (`render/Model`) — tinygltf parsing into `Mesh` objects
11. Scene management (`scene/Scene`) — multiple `GameObject`s + lights
