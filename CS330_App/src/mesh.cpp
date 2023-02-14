#include <mesh.h>
#include <iostream>
#include "shapes.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements) {
    init(vertices, elements);
}


Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<uint32_t> &elements, const glm::vec3 &color) {
    for (auto& vertex : vertices) {
        vertex.Color = color;
    }

    init(vertices, elements);
}

void Mesh::Draw() const {
    // Bind vertex array
    glBindVertexArray(_vertexArrayObject);

    // gl draw calls
    glDrawElements(GL_TRIANGLES, _elementCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::init(std::vector<Vertex>& vertices, std::vector<uint32_t>& elements) {
    for (auto i = 0; i < elements.size(); i += 3) {
        // calculate normals
        auto p1Index = elements[i];
        auto p2Index = elements[i + 1];
        auto p3Index = elements[i + 2];

        Shapes::UpdateNormals(vertices[p1Index], vertices[p2Index], vertices[p3Index]);
    }

    // create the triangle
    glGenVertexArrays(1, &_vertexArrayObject);
    glGenBuffers(1, &_vertexBufferObject);
    glGenBuffers(1, &_elementBufferObject);

    // binds vertex array object to our array
    glBindVertexArray(_vertexArrayObject);
    // activating vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
    // sending vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(elements.size() * sizeof(uint32_t)), elements.data(), GL_STATIC_DRAW);

    // define vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Color)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Uv)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    _elementCount = elements.size();
}
