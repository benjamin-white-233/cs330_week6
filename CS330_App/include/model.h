//
// Created by Ben White on 2/14/23.
//

#pragma once

#include <mesh.h>
#include <material.h>
#include "shader.h"

// The Model class is a wrapper around a mesh and a shader, so that many objects can be set up
// each having distinct shaders if necessary.
class Model {
public:
    Model(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader);
//    Material* GetMaterial() { return _material.get(); }
    Mesh* GetMesh() { return _mesh.get(); }
    Shader* GetShader() { return _shader.get(); }

private:
//    std::shared_ptr<Material> _material;
    std::shared_ptr<Mesh> _mesh;
    std::shared_ptr<Shader> _shader;
};