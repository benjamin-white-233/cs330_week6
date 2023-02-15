//
// Created by Ben White on 2/14/23.
//
//#pragma once
//#include <shader.h>
//#include <types.h>
//
//class Material {
//public:
//    explicit Material(std::shared_ptr<Shader> shader);
//
//    void AddTexture(const std::shared_ptr<Texture>& texture);
//    void Bind(const SceneParameters& sceneParameters, const glm::mat4& model);
//    Shader* GetShader() { return _shader.get(); }
//
//public:
//    float Shininess { 1.f };
//    float Roughness { 1.f };
//private:
//
//
//private:
//    std::shared_ptr<Shader> _shader { nullptr };
//    std::vector<std::shared_ptr<Texture>> _textures {};
//};