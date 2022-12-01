#include <iostream>
#include "engine/CompoundBase.hpp"

using decoder::engine::CompoundBase;

auto main() -> int {

    CompoundBase* base = new CompoundBase(std::move("../schema/schema.json"));

    std::cout << base->getSymbol(std::move("UUU")) << "\n"; // Phe F
    std::cout << base->getSymbol(std::move("UAC")) << "\n"; // Tyr Y
    std::cout << base->getSymbol(std::move("AUG")) << "\n"; // M(start)
    std::cout << base->getSymbol(std::move("GGG")) << "\n"; // Gly G

    return 0;
}
