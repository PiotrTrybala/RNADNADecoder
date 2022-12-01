#include "EngineTypes.hpp"

namespace decoder {
    namespace engine {
        namespace types {
            std::ostream& operator<<(std::ostream& os, const struct DecoderResult rhs) {
                os << rhs.result;
                return os;
            }
        }
    }
}
