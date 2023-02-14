//
// Created by Ben White on 2/13/23.
//

#pragma once
#include <game_object.h>
#include <model.h>

#include <shader.h>
#include <mesh.h>

class PointLight : public GameObject {
public:
    PointLight();
    void Init() override;
    void Update(float deltaTime) override;
    void Draw(const SceneParameters& sceneParams) override;
    void ProcessLighting(SceneParameters &sceneParams) override;

public:
    glm::vec3 AmbientColor {};
    glm::vec3 DiffuseColor {};
    glm::vec3 SpecularColor {};

    float Constant { 0.f };
    float Linear { 0.f };
    float Quadratic { 0.f };

private:
    void createShader();
    void createMesh();

private:
    std::shared_ptr<Shader> _basicUnlitShader {};
    std::shared_ptr<Mesh> _cube {};

    std::vector<Model> _models {};

    float totalTime { 0.f };
};


