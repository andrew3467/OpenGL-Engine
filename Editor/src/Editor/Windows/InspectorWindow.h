//
// Created by Andrew Graser on 9/6/2024.
//


#pragma once
#include "EditorWindow.h"

namespace GLE {
    class InspectorWindow : public EditorWindow {
    public:
        InspectorWindow();
        ~InspectorWindow() override;

        void ImGuiRender() override;
    };
}
