#include <iostream>
#include "engine/Wheel.hpp"

using std::cout;
using std::string;
using decoder::wheel::Wheel;

auto main() -> int {
    cout << "Hello World!" << "\n";

    auto* wheel = new Wheel("../wheel/wheel.json");
    delete wheel;

    return 0;
}
