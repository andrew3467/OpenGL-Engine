//
// Created by Andrew Graser on 9/4/2024.
//

#include "EditorLayer.h"

#include <glm/vec3.hpp>

#include "EditorCameraController.h"
#include "imgui.h"
#include "Core/Application.h"
#include "Windows/InspectorWindow.h"
#include "Core/Scene/ECS/Component/Components.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace GLE
{
    EditorCameraController sceneCamera;


    void EditorLayer::OnEvent(Event &e)
    {

    }

    void EditorLayer::OnCreate()
    {

    }

    void EditorLayer::OnRun()
    {
        mScene = std::make_shared<Scene>();

        sceneCamera.Init();

        auto sceneHeirarchy = new SceneHierarchy;
        sceneHeirarchy->SetScene(mScene);
        EditorWindow::PushWindow(sceneHeirarchy);

        auto inspectorWindow = new InspectorWindow;
        inspectorWindow->SetScene(mScene);
        EditorWindow::PushWindow(inspectorWindow);

        auto cubeEnt = mScene->CreateEntity("Cube");
        cubeEnt.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;
        auto& matcomp = cubeEnt.AddComponent<MaterialComponent>();
        matcomp.Material.AlbedoMap = Texture2D::Get("bricks");
    }

    void EditorLayer::OnUpdate(float dt)
    {
        sceneCamera.Update(dt);

        Renderer::StartScene(sceneCamera.GetCamera());
        mScene->Update(dt);
        Renderer::RenderScene();
    }

    void EditorLayer::OnImGuiRender()
    {
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        //Setup dockspace
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        if(dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) {
            window_flags |= ImGuiWindowFlags_NoBackground;
        }


        ImGui::SetNextWindowSize(ImVec2(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight()));
        ImGui::Begin("Dockspace", nullptr, window_flags);
        ImGui::PopStyleVar(2);
        ImGuiID dockspace_id = ImGui::GetID("Dockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        ImGui::End();

        EditorWindow::RenderWindows();

        ImGui::Begin("Frame Data");

        auto rendererStats = Renderer::GetStats();

        ImGui::Text("Renderer Stats");
        int fps = 1 / Time::GetTime();
        ImGui::Text("FPS: %i", fps);
        ImGui::Text("Num Draw Calls: %i", rendererStats.NumDrawCalls);


        ImGui::NewLine();
        glm::vec3 pos = sceneCamera.GetPosition();
        ImGui::InputFloat3("Cam Postition", &pos.x);

        ImGui::End();
    }
}
