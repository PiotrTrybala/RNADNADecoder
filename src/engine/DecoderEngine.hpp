#pragma once

#include "CompoundBase.hpp"
#include "EngineTypes.hpp"

#include <vector>

namespace decoder {

    namespace engine {
        class DecoderEngine {
            private:
                CompoundBase* base;
            public:
                DecoderEngine();
                ~DecoderEngine();

                std::vector<std::string> GetResults(const std::string& input);
                std::string GetPatrialResult(const std::string input);
        };
    }
}
