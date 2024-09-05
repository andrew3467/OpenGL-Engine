
#include "GLE/Core/Application.h"
#include "GLE/Core/Log.h"

#include "EditorLayer.h"

#include <stdexcept>

int main() {
    auto app = GLE::Application::Create(new GLE::EditorLayer);

    try{
        app->Run();
    }
    catch(std::exception& e) {
        GLE_ERROR(e.what());
    }

    delete app;
}
