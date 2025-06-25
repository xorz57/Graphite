cmake_minimum_required(VERSION 3.30)

cmake_policy(SET CMP0091 NEW)

if (VCPKG_TARGET_TRIPLET MATCHES "-static$")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else ()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(Graphite LANGUAGES CXX)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)
find_package(implot REQUIRED)

add_executable(${PROJECT_NAME}
    src/Camera.cpp
    src/ExampleLayer.cpp
    src/IndexBuffer.cpp
    src/Layer.cpp
    src/Main.cpp
    src/Shader.cpp
    src/UILayer.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE implot::implot)

include(StrictWarnings)

enable_strict_warnings(${PROJECT_NAME})
