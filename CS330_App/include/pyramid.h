//
// Created by Ben White on 2/13/23.
//

#pragma once

#include <game_object.h>
#include <shader.h>
#include <model.h>

class Pyramid : public GameObject {
public:
    Pyramid();
    void Init() override;
    void Draw(const SceneParameters &sceneParams) override;
    void Update(float deltaTime) override;
    void ProcessLighting(SceneParameters &sceneParams) override;


private:
    void createShaders();

    void createPyramid();

private:
    std::shared_ptr<Shader> _basicLitShader;
    std::shared_ptr<Shader> _textureShader;

    std::vector<Model> _models {};
};
