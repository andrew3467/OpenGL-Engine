//
// Created by Andrew Graser on 8/31/2024.
//

#ifndef IMGUILAYER_H
#define IMGUILAYER_H


#include "Core/Layer.h"


namespace GLE {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer() : Layer("ImGuiLayer") {}
        ~ImGuiLayer() = default;

        void Begin();
        void End();

        void OnEvent(Event &e) override;

        void OnCreate() override;

        void OnDestroy() override;

        private:
            void SetupDockspace();
    };
}



#endif //IMGUILAYER_H
