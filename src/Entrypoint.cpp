#include <iostream>
#include "Application.hpp"

extern decoder::Application* CreateApplication();

int main() {
    decoder::Application* app = CreateApplication();
    app->run();
    delete app;
    return 0;
}
