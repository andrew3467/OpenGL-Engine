//
// Created by Andrew Graser on 9/4/2024.
//

#include "EditorLayer.h"

#include <glm/vec3.hpp>
#include <Windows/AssetBrowserWindow.h>
#include <Renderer/RenderCommand.h>

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
    void CreateTestScene(const std::shared_ptr<Scene>& scene) {
        auto worldParent = scene->CreateEntity("World");
        auto lightParent = scene->CreateEntity("Lights");
        
        auto& worldParentTrans = worldParent.GetComponent<TransformComponent>();
        auto& lightParentTrans = lightParent.GetComponent<TransformComponent>();

        {
            auto floor = scene->CreateEntity("Floor");
            floor.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;
            floor.AddComponent<MaterialComponent>();
            auto& transform = floor.GetComponent<TransformComponent>();
            transform.Scale = {4, 0.25, 6};

            transform.SetParent(worldParent);
            worldParentTrans.AddChild(floor);
        }

        {
            auto wall = scene->CreateEntity("Wall A");
            wall.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;
            wall.AddComponent<MaterialComponent>();
            auto& transform = wall.GetComponent<TransformComponent>();
            transform.Position.x = 2;
            transform.Position.y = 1;
            transform.Scale = {0.25, 2, 6};

            transform.SetParent(worldParent);
            worldParentTrans.AddChild(wall);
        }

        {
            auto wall = scene->CreateEntity("Wall B");
            wall.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;
            wall.AddComponent<MaterialComponent>();
            auto& transform = wall.GetComponent<TransformComponent>();
            transform.Position.x = -2;
            transform.Position.y = 1;
            transform.Scale = {0.25, 2, 6};

            transform.SetParent(worldParent);
            worldParentTrans.AddChild(wall);
        }

        {
            auto wall = scene->CreateEntity("Wall C");
            wall.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;
            wall.AddComponent<MaterialComponent>();
            auto& transform = wall.GetComponent<TransformComponent>();
            transform.Position.y = 1;
            transform.Position.z = -3;
            transform.Scale = {4, 2, 0.25};

            transform.SetParent(worldParent);
            worldParentTrans.AddChild(wall);
        }

        {
            auto light = scene->CreateEntity("Point Light A");
            light.AddComponent<PointLightComponent>();
            auto& transform = light.GetComponent<TransformComponent>();

            transform.Position = {
                    0, 5, 0
            };
            transform.SetParent(lightParent);

            lightParentTrans.AddChild(light);
        }

        {
            auto light = scene->CreateEntity("Directional Light");
            light.AddComponent<DirectionalLightComponent>();

            auto& transform = light.GetComponent<TransformComponent>();
            transform.SetParent(lightParent);
            lightParentTrans.AddChild(light);

        }
    }

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

        auto assetBrowser = new AssetBrowserWindow;
        assetBrowser->SetScene(mScene);
        EditorWindow::PushWindow(assetBrowser);

        CreateTestScene(mScene);
    }

    void EditorLayer::OnUpdate(float dt)
    {
        sceneCamera.Update(dt);

        Renderer::StartScene(sceneCamera.GetCamera());
        mScene->Update(dt);
        Renderer::EndScene();
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


        ImGui::Begin("Debug");

        static bool wireframe = false;
        if(ImGui::Button("Wireframe")) {
            wireframe = !wireframe;
            RenderCommand::ToggleWireframe(wireframe);
        }

        ImGui::Spacing();
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
