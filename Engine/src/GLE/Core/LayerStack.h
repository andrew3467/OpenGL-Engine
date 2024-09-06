//
// Created by Andrew Graser on 7/26/2024.
//

#ifndef OPENGL_ENGINE_LAYERSTACK_H
#define OPENGL_ENGINE_LAYERSTACK_H

#include "Layer.h"

namespace GLE {
    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        LayerStack(const LayerStack&) = delete;
        LayerStack& operator=(const LayerStack&) = delete;

        std::vector<Layer*> GetLayers() const {return mLayers;}


    public:
        void Push(Layer* layer);
        Layer* Pop();


    private:
        std::vector<Layer*> mLayers;
    };
}

#endif //OPENGL_ENGINE_LAYERSTACK_H
