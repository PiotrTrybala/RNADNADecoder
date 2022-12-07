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


        // TODO(piotrek): to be implemented
        auto DecoderEngine::PostProcessResult(const struct DecoderResult result) -> struct DecoderResult {
            struct DecoderResult postProcessResult;

            std::string res = result.result;




            return postProcessResult;
        }

        // TODO(piotrek): to be implemented
        auto DecoderEngine::isTrailingSequence(const std::string seq) -> bool {
            return false;
        }

        auto DecoderEngine::GetResults(struct DecoderInput input) -> std::vector<struct DecoderResult> {
            std::vector<struct DecoderResult> results;
            int inputLength = input.input.length();
            int totalLength = (inputLength / 3) * 3;
            bool extend = false;
            if (totalLength != inputLength) extend = true;

            for (int i = 0; i < 3; i++) {

                struct DecoderInput partialInput = {
                    .input = input.input.substr(i, totalLength)
                };

                std::cout << "#" << (i + 1) << ": ";
                for (int i = 0; i < partialInput.input.length(); i += 3) {
                    std::cout << partialInput.input.substr(i, 3) << " ";
                }
                std::cout << " | " << GetPatrialResult(partialInput).result << "\n";

                // results.push_back(GetPatrialResult(std::move(input)));

                if (extend) totalLength++;
            }
            return results;
        }
        auto DecoderEngine::GetPatrialResult(const struct DecoderInput input) -> struct DecoderResult {
            struct DecoderResult result;
            std::string output;
            std::string raw_input = input.input;
            for (int i = 0; i < raw_input.length(); i += 3) {
                std::string seq = raw_input.substr(i, 3);
                output += base->getSymbol(seq);
            }
            result.result = output;
            return result;
        }
        auto DecoderEngine::ToString(const struct DecoderResult&& result) -> std::string {
            return result.result;
        }
    }
}
