//
// Created by Andrew Graser on 7/26/2024.
//


#include "Core/LayerStack.h"


namespace GLE {

    void LayerStack::Push(Layer *layer) {
        layer->OnCreate();

        mLayers.push_back(layer);
    }

    Layer *LayerStack::Pop() {
        return nullptr;
    }
}