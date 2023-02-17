#pragma once
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position {0.f, 0.f, 0.f};
    glm::vec3 Color {1.f, 1.f, 1.f};
    glm::vec3 Normal {0.f, 0.f, 0.f};
    glm::vec2 Uv {1.f, 1.f};
};


struct Shapes {
    static inline void UpdateNormals(Vertex& p1, Vertex& p2, Vertex& p3) {
        glm::vec3 U = p2.Position - p1.Position;
        glm::vec3 V = p3.Position - p1.Position;

        auto normal = glm::cross(U, V);

        p1.Normal = normal;
        p2.Normal = normal;
        p3.Normal = normal;
    }

    static inline std::vector<Vertex> planeVertices {
            // 0
            {
                    .Position = {-2.5f, 0.f, 4.f},
                    .Color = {0.2f, 0.6f, 0.1f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {0.f, 0.f}
            },
            // 1
            {
                    .Position = {2.5f, 0.f, 4.f},
                    .Color = {0.2f, 0.6f, 0.1f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {0.f, 1.f}
            },
            // 2
            {
                    .Position = {2.5f, 0.f, -4.f},
                    .Color = {0.2f, 0.7f, 0.9f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 1.f}
            },
            // 3
            {
                    .Position = {-2.5f, 0.f, -4.f},
                    .Color = {0.2f, 0.7f, 0.9f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 0.f}
            },
    };

    static inline std::vector<uint32_t> planeElements {
            0, 1, 2,
            2, 3, 0
    };

    static inline std::vector<Vertex> pyramidVertices{
            // front
            // 0
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.f, 0.5f, 0.5f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {0.f, 0.f}
            },
            // 1
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 1.f, 0.5f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 0.f}
            },
            // top point
            // 2
            {
                    .Position = {0.0f, 0.5f, 0.0f},
                    .Color = {0.5f, 0.5f, 1.f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {0.5f, 1.f}
            },
            // right
            // 3
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {0.f, 0.f}
            },
            // 4
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 0.f}
            },

            // base
            // 5 = 0
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.f, 0.5f, 0.5f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {0.f, 0.f}
            },
            // 6 = 1
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 1.f, 0.5f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 0.f}
            },
            // 7 = 2
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 0.5f, 1.f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {1.f, 1.f}
            },
            // 8 = 3
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Normal = {0.0f, 0.0f, 0.0f},
                    .Uv = {0.f, 1.f}
            },
    };

    static inline std::vector<uint32_t> pyramidElements{
            // sides
            0, 1, 2,
            1, 3, 2,
            3, 4, 2,
            4, 0, 2,
            // base
            5, 6, 7,
            7, 8, 5
    };

    static inline std::vector<Vertex> cubeVertices{
            // front
            // 0
            {
                    .Position = {-0.5f, 0.5f, 0.5f},
                    .Color = {1.f, 0.5f, 0.5f},
                    .Uv = {0.f, 0.f}
            },
            // 1
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {1.f, 0.5f, 0.5f},
                    .Uv = {1.f, 0.f}
            },
            // 2
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {1.f, 0.5f, 0.5f},
                    .Uv = {1.f, 1.f}
            },
            // 3
            {
                    .Position = {0.5f, 0.5f, 0.5f},
                    .Color = {1.f, 0.5f, 0.5f},
                    .Uv = {0.f, 1.f}
            },
            // right
            // 4
            {
                    .Position = {0.5f, 0.5f, 0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Uv = {0.f, 0.f}
            },
            // 5
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Uv = {1.f, 0.f}
            },
            // 6
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Uv = {1.f, 1.f}
            },
            // 7
            {
                    .Position = {0.5f, 0.5f, -0.5f},
                    .Color = {0.5f, 0.5f, 0.5f},
                    .Uv = {0.f, 1.f}
            },
            // back
            // 8
            {
                    .Position = {0.5f, 0.5f, -0.5f},
                    .Color = {1.f, 1.f, 0.5f},
                    .Uv = {0.f, 0.f}
            },
            // 9
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {1.f, 1.f, 0.5f},
                    .Uv = {1.f, 0.f}
            },
            // 10
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {1.f, 1.f, 0.5f},
                    .Uv = {1.f, 1.f}
            },
            // 11
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
                    .Color = {1.f, 1.f, 0.5f},
                    .Uv = {0.f, 1.f}
            },
            // left
            // 12
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
                    .Color = {0.f, 0.5f, 0.f},
                    .Uv = {0.f, 0.f}
            },
            // 13
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.f, 0.5f, 0.f},
                    .Uv = {1.f, 0.f}
            },
            // 14
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {0.f, 0.5f, 0.f},
                    .Uv = {1.f, 1.f}
            },
            // 15
            {
                    .Position = {-0.5f, 0.5f, 0.5f},
                    .Color = {0.f, 0.5f, 0.f},
                    .Uv = {0.f, 1.f}
            },
            // top
            // 16
            {
                    .Position = {-0.5f, 0.5f, -0.5f},
                    .Color = {0.f, 1.f, 0.f},
                    .Uv = {0.f, 0.f}

            },
            // 17
            {
                    .Position = {-0.5f, 0.5f, 0.5f},
                    .Color = {0.f, 1.f, 0.f},
                    .Uv = {1.f, 0.f}

            },
            // 18
            {
                    .Position = {0.5f, 0.5f, 0.5f},
                    .Color = {0.f, 1.f, 0.f},
                    .Uv = {1.f, 1.f}

            },
            // 19
            {
                    .Position = {0.5f, 0.5f, -0.5f},
                    .Color = {0.f, 1.f, 0.f},
                    .Uv = {0.f, 1.f}
            },
            // bottom
            // 20
            {
                    .Position = {0.5f, -0.5f, 0.5f},
                    .Color = {0.f, 0.5f, 0.f},
                    .Uv = {0.f, 0.f}
            },
            // 21
            {
                    .Position = {0.5f, -0.5f, -0.5f},
                    .Color = {0.f, 0.5f, 0.f},
                    .Uv = {1.f, 0.f}

            },
            // 22
            {
                    .Position = {-0.5f, -0.5f, -0.5f},
                    .Color = {0.f, 0.5f, 0.f},
                    .Uv = {1.f, 1.f}
            },
            // 23
            {
                    .Position = {-0.5f, -0.5f, 0.5f},
                    .Color = {0.f, 0.5f, 0.f},
                    .Uv = {0.f, 1.f}
            }
    };

    static inline std::vector<uint32_t> cubeElements{
            0, 1, 3, 1, 2, 3, // front
            4, 5, 7, 5, 6, 7, // right
            8, 9, 11, 9, 10, 11, // back
            12, 13, 15, 13, 14, 15, // left
            16, 17, 19, 17, 18, 19, // top
            20, 21, 23, 21, 22, 23 // bottom
    };
};