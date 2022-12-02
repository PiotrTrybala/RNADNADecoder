#include <iostream>
#include "engine/DecoderEngine.hpp"
#include "engine/EngineTypes.hpp"

using namespace decoder::engine;

auto main() -> int {
    auto* engine = new DecoderEngine();
    struct DecoderInput input = {
        .input = "AAAUGAACGAAAAUCUGUUCGCUUCAUUCAUUGCCCCCACAAUCCUAGGCCUACCC"
    };
    std::vector<struct DecoderResult> results = engine->GetResults(input);
    // for (int i = 0; i < 3; i++) {
    //     std::cout << "#" << (i + 1) << ": " << results[i].result << "\n";
    // }
    delete engine;
    return 0;
}
