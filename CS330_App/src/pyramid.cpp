//
// Created by Ben White on 2/13/23.
//

#include <pyramid.h>
#include <types.h>
#include <glm/gtc/matrix_transform.hpp>
#include <shapes.h>
#include <string>

Pyramid::Pyramid() {
    createShaders();
    createPyramid();
}

void Pyramid::Init() {

}

void Pyramid::Update(float deltaTime) {

}

void Pyramid::Draw(const SceneParameters& sceneParams) {
    Shader* lastBoundshader = nullptr;
    for (auto& model : _models) {
        auto* shader = model.GetShader();
        auto* mesh = model.GetMesh();

        if (shader != lastBoundShader) {
            shader->Bind();
            shader->SetMat4("projection", sceneParams.ProjectionMatrix);
            shader->SetMat4("view", sceneParams.ViewMatrix);

            shader->SetVec3("eyePos", sceneParams.CameraPosition);

            // lights
            for (auto i = 0; i < MAX_POINT_LIGHTS; i++) {
                std::string baseUniformName = "pointLights";
                baseUniformName += std::to_string(i) + "]";

                PointLightStruct pointLight = i < sceneParams.Lights.size() ? sceneParams.Lights[i] : PointLightStruct{};
                shader->SetVec3(baseUniformName + ".Position", pointLight.Position);
                shader->SetVec3(baseUniformName + ".Diffuse", pointLight.DiffuseColor);
                shader->SetVec3(baseUniformName + ".Ambient", pointLight.AmbientColor);
                shader->SetVec3(baseUniformName + ".Specular", pointLight.SpecularColor);

                shader->SetFloat(baseUniformName + ".Constant", pointLight.Constant);
                shader->SetFloat(baseUniformName + ".Linear", pointLight.Linear);
                shader->SetFloat(baseUniformName + ".Quadratic", pointLight.Quadratic);
            }

            shader->SetVec3("dirLight.Direction", sceneParams.DirLight.Direction);
            shader->SetVec3("dirLight.Diffuse", sceneParams.DirLight.DiffuseColor);
            shader->SetVec3("dirLight.Ambient", sceneParams.DirLight.AmbientColor);
            shader->SetVec3("dirLight.Specular", sceneParams.DirLight.SpecularColor);
        }

        shader->SetMat4("model", Transform * mesh->Transform);
        mesh->Draw();
    }
}

void Pyramid::ProcessLighting(SceneParameters &sceneParams) {
    return;
}

void Pyramid::createShaders() {
    _basicLitShader = std::make_shared<Shader>(Path("basic_lit.vert"), Path("basic_lit.frag"));
    auto pyramidTexture = std::make_shared<Texture>("container.jpg");

    _basicLitShader->AddTexture(pyramidTexture);
}

void Pyramid::createPyramid() {
    // creating different meshes for each shape and manipulating the position
    auto pyramidMesh = std::make_shared<Mesh>(Shapes::pyramidVertices, Shapes::pyramidElements);

    _models.emplace_back(pyramidMesh, _basicLitShader);

    pyramidMesh->Transform = glm::translate(pyramid.Transform, glm::vec3(1.f, -0.5f, 0.0f));
}