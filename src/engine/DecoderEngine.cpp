
#include <iostream>

#include "DecoderEngine.hpp"
#include "spdlog/spdlog.h"

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

        auto IsRightMultiple(int input) -> bool {
            int multiple_length = (input / 3) * 3;
            return input != multiple_length;
        }

        auto DecoderEngine::GetResults(const std::string& input) -> std::vector<std::string> {
            std::vector<std::string> results;
            bool extend = IsRightMultiple(input.length());
            int total_length {input.length() / 3 * 3};
            for (int i = 0; i < 3; i++) {
                results.push_back(GetPatrialResult(std::move(input)));
                if (extend) total_length++;
            }
            return results;
        }
        auto DecoderEngine::GetPatrialResult(const std::string input) -> std::string {
            std::string output{""}, raw_input {input};
            spdlog::get("console")->info("Decoding sequence: {}", raw_input);
            for (int i = 0; i < raw_input.length(); i += 3) {
                std::string seq { raw_input.substr(i, 3) };

                #ifdef DEBUG_DECODERENGINE_GETPATRIALRESULT
                    spdlog::get("console")->info("Decoding partial sequence: {}\n", seq);
                #endif

                output += base->GetSymbol(seq);
            }
            return output;
        }
    }
}
