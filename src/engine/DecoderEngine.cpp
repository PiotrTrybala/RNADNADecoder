
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

        auto DecoderEngine::GetResults(const std::string& input) -> std::vector<std::string> {
            std::vector<std::string> results;
            bool extend = false;
            int input_length = input.length();
            std::cout << input_length << " | il" << std::endl;
            int total_length {(input_length / 3) * 3};
            std::cout << total_length << " | tl" << std::endl;
            if (input_length != total_length) extend = true;
            for (int i = 0; i < 3; i++) {
                std::string substr_input {input};
                results.push_back(GetPatrialResult(std::move(substr_input.substr(i, total_length))));
                if (extend) total_length++;
            }
            return results;
        }
        auto DecoderEngine::GetPatrialResult(const std::string input) -> std::string {
            std::string output{""}, raw_input {input};
            #ifdef DEBUG_DECODERENGINE_GETPARTIALRESULT
            spdlog::get("console")->info("Decoding sequence: {}", raw_input);
            #endif
            for (int i = 0; i < raw_input.length(); i += 3) {
                std::string seq { raw_input.substr(i, 3) };

                #ifdef DEBUG_DECODERENGINE_GETPATRIALRESULT
                    spdlog::get("console")->info("Decoding partial sequence: {}\n", seq);
                #endif

                output += base->GetSymbol(seq);
            }
            std::cout << "partial result: " << output << std::endl;
            return output;
        }
    }
}
