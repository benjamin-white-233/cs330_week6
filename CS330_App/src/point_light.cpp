//
// Created by Ben White on 2/13/23.
//

#include <point_light.h>
#include <shapes.h>
#include <glm/ext/matrix_transform.hpp>
#include <model.h>
#include <shader.h>
#include <mesh.h>

PointLight::PointLight() {
    createShader();
    createMesh();
}

void PointLight::Init() {
}

void PointLight::Update(float deltaTime) {
    auto cos = std::cos(totalTime);
    auto sin = std::sin(totalTime);

    Transform = glm::translate(Transform, glm::vec3(cos / 10, 0, sin / 10));

    totalTime += deltaTime;
}

void PointLight::Draw(const SceneParameters& sceneParams) {
    for (auto& model : _models) {
        auto* shader = model.GetShader();
        auto* mesh = model.GetMesh();
        shader->Bind();
        shader->SetMat4("projection", sceneParams.ProjectionMatrix);
        shader->SetMat4("view", sceneParams.ViewMatrix);
        shader->SetMat4("model", Transform * mesh->Transform);

        mesh->Draw();
    }
}

void PointLight::ProcessLighting(SceneParameters &sceneParams) {
    if (sceneParams.Lights.size() < MAX_POINT_LIGHTS) {
        PointLightStruct pointLight {
          .Position =  glm::vec3(Transform[3]),
          .AmbientColor = AmbientColor,
          .DiffuseColor = DiffuseColor,
          .SpecularColor = SpecularColor,
          .Constant = Constant,
          .Linear = Linear,
          .Quadratic = Quadratic,
        };

        sceneParams.Lights.emplace_back(pointLight);
    }
}

void PointLight::createShader() {
    _basicUnlitShader = std::make_shared<Shader>(Path("basic_unlit_color.vert"), Path("basic_unlit_color.frag"));
}

void PointLight::createMesh() {
    auto pyramid = std::make_shared<Mesh>(Shapes::pyramidVertices, Shapes::pyramidElements);
    auto& pyramidModel = _models.emplace_back(pyramid, _basicUnlitShader);
}



