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

                std::vector<struct DecoderResult> GetResults(struct DecoderInput input);
                struct DecoderResult GetPatrialResult(const struct DecoderInput input);

                struct DecoderResult PostProcessResult(const struct DecoderResult result);

                bool isTrailingSequence(const std::string seq);

                std::string ToString(const struct DecoderResult&& result);
        };
    }
}
