//
// Created by Andrew Graser on 9/4/2024.
//


#pragma once

#include "Core/Application.h"

extern GLE::Application* GLE::CreateApplication();

int main(int argc, char** argv) {
    GLE::Log::Init();

    //TODO: Pass in command line args
    auto app = GLE::CreateApplication();
    app->Run();

    delete app;
}
