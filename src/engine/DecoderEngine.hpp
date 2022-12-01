#include "CompoundBase.hpp"
#include <vector>

using decoder::engine::types::DecoderResult;

namespace decoder {

    namespace engine {
        class DecoderEngine {
            private:
                CompoundBase* base;



            public:
                DecoderEngine();
                ~DecoderEngine();


                std::vector<struct DecoderResult> GetResults(const struct DecoderInput&& input);
                struct DecoderResult& GetPatrialResult(const struct DecoderInput&& input);
                std::string ToString(const struct DecoderResult&& result);
        };
    }
}
