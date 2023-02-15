#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <camera.h>
#include <mesh.h>
#include <game_object.h>

class Application {
public:
    Application(std::string WindowTitle, int width, int height);
    void Run();

private:
    bool openWindow();
    void setupInputs();

    void setupScene();
    bool update(float deltaTime);
    bool draw();

    void handleInput(float deltaTime);
    void mousePositionCallback(double xpos, double ypos);

    void IncrementSpeed(double amount);

private:
    std::string _applicationName {};
    int _width {};
    int _height {};
    GLFWwindow* _window { nullptr };

    float _moveSpeed { 5.f };
    Camera _camera;
    std::vector<std::unique_ptr<GameObject>> _objects {};

    bool _running { false };

    bool _firstMouse { false };
    glm::vec2 _lastMousePosition {};
    glm::vec2 _cameraLookSpeed {};

    float _lastFrameTime { -1.f };

    // lighting
    float _ambientStrength { 0.1f };
    glm::vec3 _ambientLightColor {1.f, 1.f, 1.f};

    GLuint _containerTexture;
};