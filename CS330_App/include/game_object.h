//
// Created by Ben White on 2/13/23.
//
#pragma once
#include <glm/glm.hpp>
#include <types.h>
#include <model.h>

// Game objects,
class GameObject {
public:
    virtual ~GameObject() = default;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw(const SceneParameters& sceneParams) = 0;
    virtual void ProcessLighting(SceneParameters& sceneParams) = 0;
public:
    glm::mat4 Transform { 1.f }; // default model matrix
    std::vector<Model> _models {};
};