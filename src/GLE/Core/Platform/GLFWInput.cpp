//
// Created by Andrew Graser on 8/28/2024.
//

#include "Core/Input.h"
#include "Core/Application.h"


#include "GLFW/glfw3.h"

namespace GLE {
    bool Input::GetKey(uint32_t keycode) {
        return glfwGetKey((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), keycode);
    }

    bool Input::GetMouseButton(uint32_t mousecode) {
        return glfwGetMouseButton((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), mousecode);
    }
}
