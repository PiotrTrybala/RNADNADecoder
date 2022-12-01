#include "Application.hpp"

class MyApplication : public decoder::Application {
    public:
        void run() override {
            std::cout << "Hello World!\n";
        }
};

decoder::Application* CreateApplication() {
    return new MyApplication();
}
