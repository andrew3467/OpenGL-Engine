//
// Created by Andrew Graser on 9/4/2024.
//

#include "EditorLayer.h"

#include <glm/vec3.hpp>

#include "imgui.h"
#include "Core/CameraController.h"
#include "Core/Scene/ECS/Entity.h"
#include "Core/Scene/ECS/Component/PrimitiveRendererComponent.h"
#include "Renderer/Camera.h"
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

        StandardShader = Shader::Create("../../assets/shaders/Standard.glsl");

        mainCamera.AddCamera(std::make_shared<Camera>(glm::vec3(0,0,-6)));


        auto entity = mScene->CreateEntity("Test Object");
        entity.AddComponent<PrimitiveRendererComponent>().RenderType = PrimitiveType::Cube;
    }

    void EditorLayer::OnUpdate(float dt) {
        mainCamera.Update(dt);
        mScene->Update(dt);

        mScene->Render(*StandardShader);
    }

    void EditorLayer::OnImGuiRender() {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        mSceneHeirarchy.Render();

        ImGui::Begin("Frame Data");

        glm::vec3 pos = mainCamera.GetPosition();
        ImGui::InputFloat3("Cam Postition", &pos.x);

        ImGui::End();
    }
}
