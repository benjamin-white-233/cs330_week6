#include <application.h>
#include <iostream>
#include <types.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <stb_image.h>

Application::Application(std::string WindowTitle, int width, int height)
    : _applicationName{ WindowTitle }, _width{ width }, _height{ height },
    _camera {width, height, {-2.f, 0.f, 5.f}, true },
    _cameraLookSpeed {0.1f, 0.1f}
    {}

void Application::Run() {
    // Open the window
    if (!openWindow()) {
        return;
    }

    setupInputs();
    _running = true;

    // Set up the scene
    setupScene();

    // Run application
    while (_running) {
        float currentTime = glfwGetTime();

        if (_lastFrameTime == -1.f) {
            _lastFrameTime = currentTime;
        }

        auto deltaTime = currentTime - _lastFrameTime;
        _lastFrameTime = currentTime;

        if (glfwWindowShouldClose(_window)) {
            _running = false;
            continue;
        }
        // Update
        update(deltaTime);
        // Draw
        draw();
    }
    glfwTerminate();
}

bool Application::openWindow() {
    // initialize glad to v3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // creating the window, 800x600
    _window = glfwCreateWindow(800, 600, "Benjamin White", nullptr, nullptr);

    if (!_window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
    }

    // sets _widow to the current thread
    glfwMakeContextCurrent(_window);
    glfwSetWindowUserPointer(_window, (void*)this);

    // adjusting the viewport if window is resized
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);

        auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        app->_width = width;
        app->_height = height;

        app->_camera.SetSize(width, height);
    });

    // if GLAD cannot be loaded, return false
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    // otherwise, return true
    return true;
}


void Application::setupInputs() {
    glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        // establishing key press actions
        switch (key) {
            case GLFW_KEY_ESCAPE: {
                if (action == GLFW_PRESS) {
                    app->_running = false;
                }
                break;
            }
            // switch to ortho camera
            case GLFW_KEY_P: {
                if (action == GLFW_PRESS) {
                    app->_camera.SetIsPerspective(!app->_camera.IsPerspective());
                }
            }
            default: {}
        }
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        app->mousePositionCallback(xpos, ypos);
    });

    glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        app->IncrementSpeed(yOffset);

        std::cout << "Mouse wheel (" << xOffset << ", " << yOffset << ")" << std::endl;
    });

    glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT: {
                if (action == GLFW_PRESS) {
                    std::cout << "Mouse button left pressed" << std::endl;
                }
                else {

                }
                break;
            }
            case GLFW_MOUSE_BUTTON_MIDDLE: {
                if (action == GLFW_PRESS) {
                    std::cout << "Mouse button middle pressed" << std::endl;
                }
                else {

                }
                break;
            }
            case GLFW_MOUSE_BUTTON_RIGHT: {
                if (action == GLFW_PRESS) {
                    std::cout << "Mouse button right pressed" << std::endl;
                }
                else {

                }
                break;
            }
            default:
                std::cout << "Unhangled mouse button event" << std::endl;

        }
    });
}

void Application::setupScene() {
    // creating different meshes for each shape and manipulating the position
    auto& pyramid = _meshes.emplace_back(Shapes::pyramidVertices, Shapes::pyramidElements);
    pyramid.Transform = glm::translate(pyramid.Transform, glm::vec3(1.f, -0.5f, 0.0f));

    // declaring paths to shaderfiles
    Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";
    _shader = Shader( shaderPath / "basic_shader.vert" , shaderPath / "basic_shader.frag");

    // defining path to texture file
    Path texturePath = std::filesystem::current_path() / "assets" / "textures";
    auto containerPath = (texturePath / "container.jpg").string();

    int width, height, numChannels;
    // loading texture
    unsigned char* data = stbi_load(containerPath.c_str(), &width, &height, &numChannels, STBI_rgb_alpha);

    // generating and binding texture
    glGenTextures(1, &_containerTexture);
    glBindTexture(GL_TEXTURE_2D, _containerTexture);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,  GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cerr << "Failed to load texture at path: " << containerPath << std::endl;
    }
    // delete data origin
    stbi_image_free(data);
}

bool Application::update(float deltaTime) {
    glfwPollEvents();

    handleInput(deltaTime);

    return false;
}

bool Application::draw() {
    // background color
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // camera
    // set model view projection matrix
    glm::mat4 view = _camera.GetViewMatrix();
    glm::mat4 projection = _camera.GetProjectionMatrix();

    // set matrices in the shader
    _shader.Bind();
    _shader.SetMat4("projection", projection);
    _shader.SetMat4("view", view);

    glBindTexture(GL_TEXTURE_2D, _containerTexture);

    // draw each mesh
    for (auto& mesh : _meshes) {
        // sending each individual mesh.Transform to the shader
        _shader.SetMat4("model", mesh.Transform);
        mesh.Draw();
    }

    glfwSwapBuffers(_window);
    return false;
}

// assigning keys to a movement direction
void Application::handleInput(float deltaTime) {

    auto moveAmount = abs(_moveSpeed * deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_W)) {
        _camera.MoveCamera(Camera::MoveDirection::Forward, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_A)) {
        _camera.MoveCamera(Camera::MoveDirection::Left, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_S)) {
        _camera.MoveCamera(Camera::MoveDirection::Backward, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_D)) {
        _camera.MoveCamera(Camera::MoveDirection::Right, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_Q)) {
        _camera.MoveCamera(Camera::MoveDirection::Up, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_E)) {
        _camera.MoveCamera(Camera::MoveDirection::Down, moveAmount);
    }

    double xpos, ypos;
    glfwGetCursorPos(_window, &xpos, &ypos);

    mousePositionCallback(xpos, ypos);
}

void Application::mousePositionCallback(double xpos, double ypos) {
    if (!_firstMouse) {
        _lastMousePosition.x = static_cast<float>(xpos);
        _lastMousePosition.y = static_cast<float>(ypos);
        _firstMouse = true;
    }

    glm::vec2 moveAmount {
        xpos - _lastMousePosition.x,
        _lastMousePosition.y - ypos,
    };

    _lastMousePosition.x = xpos;
    _lastMousePosition.y = ypos;

    _camera.RotateBy(moveAmount.x * _cameraLookSpeed.x, moveAmount.y * _cameraLookSpeed.y);
}

// incrementing camera movement speed
void Application::IncrementSpeed(double amount) {
    _moveSpeed += amount;
}
