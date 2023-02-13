set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist/${CMAKE_SYSTEM_NAME}/${PROJECT_NAME})

add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/stb_image)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE GLAD_SOURCES external/GLAD/glad/*.c)

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCES} src/camera.cpp include/camera.h)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
        glfw
        glm
        external/GLAD
        stb
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glm
        OpenGL::GL
        stb
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)