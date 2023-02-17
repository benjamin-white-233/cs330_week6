#pragma once
#include <vector>
#include <types.h>
#include <glad/glad.h>

class Mesh {
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    void Draw();

    glm::mat4 Transform {1.f};

private:
    void init(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements);
private:
    uint32_t _elementCount {0};
    GLuint _vertexBufferObject {};
    GLuint _shaderProgram {};
    GLuint _vertexArrayObject {};
    GLuint _elementBufferObject {};
};