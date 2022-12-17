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

        auto DecoderEngine::GetResults(const std::string& input) -> std::vector<std::string> {
            std::vector<std::string> results;
            int inputLength = input.length();
            int totalLength = (inputLength / 3) * 3;
            bool extend = false;
            if (totalLength != inputLength) extend = true;

            for (int i = 0; i < 3; i++) {
                results.push_back(GetPatrialResult(std::move(input)));
                if (extend) totalLength++;
            }
            return results;
        }
        auto DecoderEngine::GetPatrialResult(const std::string input) -> std::string {
            std::string output;
            std::string raw_input = input;
            for (int i = 0; i < raw_input.length(); i += 3) {
                std::string seq = raw_input.substr(i, 3);
                output += base->getSymbol(seq);
            }
            return output;
        }
    }
}
