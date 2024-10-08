//
// Created by Andrew Graser on 8/31/2024.
//

#include "ImGuiLayer.h"

#include <entt/entity/entity.hpp>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3_loader.h"

#include "Core/Application.h"
#include "Core/Window.h"
#include "GLFW/glfw3.h"


namespace GLE {
    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();
        auto& app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnEvent(Event &e) {

    }

    void ImGuiLayer::OnCreate() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();

        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        const char* glVersion = "#version 330";
        ImGui_ImplOpenGL3_Init(glVersion);
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::Get().GetWindow().GetNativeWindow(), true);

        io.IniFilename = "imgui.ini";
        ImGui::LoadIniSettingsFromDisk("imgui.ini");

        SetupDockspace();
    }

    void ImGuiLayer::OnDestroy() {
        //Update ini file
        ImGui::SaveIniSettingsToDisk("imgui.ini");


        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::SetupDockspace() {

    }
}
