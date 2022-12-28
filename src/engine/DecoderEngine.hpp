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

                /**
                 * @brief Parses input which is chain of compounds and outputs resulting chain of amino acids
                 *
                 * @param input chain of raw compounds
                 *
                 * @return std::vector<std::string> chains of amino acids decoded from inputs
                 */
                std::vector<std::string> GetResults(const std::string& input);
                /**
                 * @brief Helper method for GetResults for decoding single version of chain
                 *
                 * @param input chain of raw compoundss
                 * @return std::string decoded chain
                 */
                std::string GetPatrialResult(const std::string input);
        };
    }
}
