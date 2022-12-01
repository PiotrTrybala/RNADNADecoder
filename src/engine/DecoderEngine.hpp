#include "CompoundBase.hpp"

using decoder::engine::types::DecoderResult;

namespace decoder {

    namespace engine {
        class DecoderEngine {

            private:

                CompoundBase* base;
            public:
                DecoderEngine();
                ~DecoderEngine();

                struct DecoderResult& GetResult(const struct DecoderInput&& input);
                std::string ToString(const struct DecoderResult&& result);
        };
    }
}
