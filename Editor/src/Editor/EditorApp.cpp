//
// Created by Andrew Graser on 9/4/2024.
//


#include "GLE/Core/Application.h"

#include "EditorLayer.h"

#include "GLE/Core/EntryPoint.h"

namespace GLE {
    class EditorApp : public Application {
        public:
        EditorApp() {
            PushLayer(new EditorLayer());
        }
    };

    Application* CreateApplication() {
        return new EditorApp();
    }
}