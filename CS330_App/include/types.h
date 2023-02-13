#pragma once
#include <glm/glm.hpp>


struct Vertex {
    glm::vec3 Position {0.f, 0.f, 0.f};
    glm::vec3 Color {1.f, 1.f, 1.f};
    glm::vec3 Normal {0.f, 0.f, 0.f};
    glm::vec2 Uv {1.f, 1.f};
};


struct Shapes {
    static inline std::vector<Vertex> pyramidVertices {
            // front
            // 0
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {1.f, 0.5f, 0.5f},
                    .Uv = {0.f, 0.f}
            },
            // 1
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 1.f, 0.5f},
                    .Uv = {1.f, 0.f}
            },
            // top point
            // 2
            {
                    .Position = {0.0f, 0.5f, 0.0f},
                    .Color = {0.5f, 0.5f, 1.f},
                    .Uv = {0.5f, 1.f}
            },
            // right
            // 3
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Uv = {0.f, 0.f}
            },
            // 4
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Uv = {1.f, 0.f}
            },

            // base
            // 5 = 0
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {1.f, 0.5f, 0.5f},
                    .Uv = {0.f, 0.f}
            },
            // 6 = 1
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 1.f, 0.5f},
                    .Uv = {1.f, 0.f}
            },
            // 7 = 2
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 0.5f, 1.f},
                    .Uv = {1.f, 1.f}
            },
            // 8 = 3
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Uv = {0.f, 1.f}
            },
    };

    static inline std::vector<uint32_t> pyramidElements {
            // sides
            0, 1, 2,
            1, 3, 2,
            3, 4, 2,
            4, 0, 2,
            // base
            5, 6, 7,
            7, 8, 5
    };
};