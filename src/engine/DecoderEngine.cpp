#include "DecoderEngine.hpp"
#include <iostream>

namespace decoder
{
    namespace engine
    {
        DecoderEngine::DecoderEngine()
        {
            base = new CompoundBase("../schema/schema.json"); // add customizable path to schema file
        }
        DecoderEngine::~DecoderEngine()
        {
            delete base;
        }

        std::vector<struct DecoderResult> DecoderEngine::GetResults(struct DecoderInput input) {
            std::vector<struct DecoderResult> results;
            int inputLength = input.input.length();
            int totalLength = (int)(inputLength / 3) * 3;
            bool extend = false;
            if (totalLength != inputLength) extend = true;

            for (int i = 0; i < 3; i++) {
                struct DecoderInput input = {
                    .input = input.input.substr(i, totalLength)
                };

                results.push_back(GetPatrialResult(std::move(input)));

                if (extend) totalLength++;
            }
            return results;
        }
        struct DecoderResult DecoderEngine::GetPatrialResult(const struct DecoderInput&& input) {
            struct DecoderResult result;
            std::string output;
            std::string raw_input = input.input;
            for (int i = 0; i < raw_input.length(); i += 3) {
                std::string seq = raw_input.substr(i, 3);
                std::cout << "#" << (i + 1) << ": " << seq << "\n";
                output += base->getSymbol(seq);
            }
            result.result = output;
            return result;
        }
        std::string DecoderEngine::ToString(const struct DecoderResult&& result) {
            return result.result;
        }
    }
}
