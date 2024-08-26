
#include "Core/Application.h"

#include "SandboxLayer.h"

int main() {
    auto app = GLE::Application::Create(new SandboxLayer);

    try{
        app->Run();
    }
    catch(std::exception& e) {
        GLE_ERROR(e.what());
    }

    delete app;
}
