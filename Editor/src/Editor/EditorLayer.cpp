//
// Created by Andrew Graser on 9/4/2024.
//

#define ASSETS_FOLDER "../../assets/"

#include "EditorLayer.h"

#include <glm/vec3.hpp>

#include "imgui.h"
#include "Windows/InspectorWindow.h"
#include "Core/CameraController.h"
#include "Core/Scene/ECS/Entity.h"
#include "Core/Scene/ECS/Component/Components.h"
#include "Renderer/Camera.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace GLE
{
    CameraController mainCamera;

    std::shared_ptr<Shader> StandardShader;


    void EditorLayer::OnEvent(Event &e)
    {

    }

    void EditorLayer::OnCreate()
    {

    }

    void EditorLayer::OnRun()
    {
        mScene = std::make_shared<Scene>();
        mSceneHeirarchy.SetScene(mScene);

        StandardShader = Shader::Create("shaders/Standard.glsl");

        mainCamera.AddCamera(std::make_shared<Camera>(glm::vec3(0, 0, 6)));

        auto sceneHeirarchy = new SceneHierarchy;
        sceneHeirarchy->SetScene(mScene);

        EditorWindow::PushWindow(sceneHeirarchy);

        auto inspectorWindow = new InspectorWindow;
        inspectorWindow->SetScene(mScene);

        EditorWindow::PushWindow(inspectorWindow);


        auto entity = mScene->CreateEntity("Test Object");
        entity.AddComponent<PrimitiveRendererComponent>();

        auto child = mScene->CreateEntity("Test Child");
        child.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;

        entity.GetComponent<TransformComponent>().AddChild(child);
        child.GetComponent<TransformComponent>().SetParent(entity);
    }

    void EditorLayer::OnUpdate(float dt)
    {
        mainCamera.Update(dt);
        mScene->Update(dt);

        Renderer::StartScene(mainCamera.GetCamera());
        mScene->Render(*StandardShader);
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

        ImGui::SetNextWindowSize(ImVec2(1280, 720));
        ImGui::Begin("Dockspace", nullptr, window_flags);
        ImGui::PopStyleVar(2);
        ImGuiID dockspace_id = ImGui::GetID("Dockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        ImGui::End();

        EditorWindow::RenderWindows();

        ImGui::Begin("Frame Data");

        auto rendererStats = Renderer::GetStats();

        ImGui::Text("Renderer Stats");
        ImGui::Text("Num Draw Calls: %i", rendererStats.NumDrawCalls);
        ImGui::NewLine();

        glm::vec3 pos = mainCamera.GetPosition();
        ImGui::InputFloat3("Cam Postition", &pos.x);

        ImGui::End();
    }
}
