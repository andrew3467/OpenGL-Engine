//
// Created by Andrew Graser on 9/4/2024.
//

#define ASSETS_FOLDER "../../assets/"

#include "EditorLayer.h"

#include <glm/vec3.hpp>

#include "imgui.h"
#include "InspectorWindow.h"
#include "Core/CameraController.h"
#include "Core/Scene/ECS/Entity.h"
#include "Core/Scene/ECS/Component/Components.h"
#include "Renderer/Camera.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace GLE {
    CameraController mainCamera;

    std::shared_ptr<Shader> StandardShader;


    void EditorLayer::OnEvent(Event &e) {

    }

    void EditorLayer::OnCreate() {

    }

    void EditorLayer::OnRun() {
        mScene = std::make_shared<Scene>();
        mSceneHeirarchy.SetScene(mScene);

        StandardShader = Shader::Create("shaders/Standard.glsl");

        mainCamera.AddCamera(std::make_shared<Camera>(glm::vec3(0,0,6)));

        auto sceneHeirarchy = new SceneHeirarchy;
        sceneHeirarchy->SetScene(mScene);

        EditorWindow::PushWindow(sceneHeirarchy);

        auto inspectorWindow = new InspectorWindow;
        inspectorWindow->SetScene(mScene);

        EditorWindow::PushWindow(inspectorWindow);


        auto entity = mScene->CreateEntity("Test Object");

        auto child = mScene->CreateEntity("Test Child");
        child.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;

        auto parentTrans = entity.GetComponent<TransformComponent>();
        auto childTrans = child.GetComponent<TransformComponent>();

        parentTrans.AddChild(&childTrans);
    }

    void EditorLayer::OnUpdate(float dt) {
        mainCamera.Update(dt);
        mScene->Update(dt);

        Renderer::StartScene(mainCamera.GetCamera());
        mScene->Render(*StandardShader);
        Renderer::RenderScene();
    }

    void EditorLayer::OnImGuiRender() {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

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
