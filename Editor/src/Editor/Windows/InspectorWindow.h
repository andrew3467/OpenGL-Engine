//
// Created by Andrew Graser on 9/6/2024.
//


#pragma once
#include <glm/vec3.hpp>

#include "EditorWindow.h"
#include "Renderer/Texture.h"

namespace GLE {
    class Shader;
}

namespace GLE {
    class InspectorWindow : public EditorWindow {
    public:
        InspectorWindow();
        ~InspectorWindow() override;

        void ImGuiRender() override;



        void DrawVec3(const std::string& name, glm::vec3& vec);
        std::shared_ptr<Texture2D> DrawTextureSelectionWindow(std::shared_ptr<Texture2D>& currentTex, const std::string& title);
        std::shared_ptr<Shader> DrawShaderSelectionWindow(std::shared_ptr<Shader>& currentShader);


        template<typename C>
        void AddComponentDisplay(const std::string& name);
    };
}
