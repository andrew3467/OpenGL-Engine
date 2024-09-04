//
// Created by Andrew Graser on 8/31/2024.
//

#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3_loader.h"

#include "Core/Application.h"
#include "Core/Window.h"


namespace GLE {
    void ImGuiLayer::OnEvent(Event &e) {

    }

    void ImGuiLayer::OnCreate() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO(); (void)io;

        const char* glVersion = "#version 330";
        ImGui_ImplOpenGL3_Init(glVersion);
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), true);
    }

    void ImGuiLayer::OnRender() {




    }

    void ImGuiLayer::OnDestroy() {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
