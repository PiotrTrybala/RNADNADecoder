#include "DecoderEngine.hpp"
#include <iostream>

namespace decoder
{
    namespace engine
    {

        using types::DecoderInput;
        using types::DecoderResult;

        DecoderEngine::DecoderEngine()
        {
            base = new CompoundBase("../schema/schema.json"); // add customizable path to schema file
        }
        DecoderEngine::~DecoderEngine()
        {
            delete base;
        }

        std::vector<struct DecoderResult> DecoderEngine::GetResults(const struct DecoderInput&& input) {
            std::vector<struct DecoderResult> results;
            int inputLength = input.input.length();
            int totalLength = (int)(inputLength / 3) * 3;
            bool extend = false;
            if (totalLength != inputLength) extend = true;

            for (int i = 0; i < 3; i++) {

                std::string coded = input.input.substr(i, totalLength);
                if (extend) totalLength++;

                std::cout << "+" << (i + 1) << ": " << coded << "\n";

            }
            return results;
        }
        struct DecoderResult& DecoderEngine::GetPatrialResult(const struct DecoderInput&& input) {

        }
        std::string DecoderEngine::ToString(const struct DecoderResult&& result) {
            return result.result;
        }
    }
}
