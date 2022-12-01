#include <vector>
#include <cstring>
#include <unordered_map>

namespace decoder
{
    namespace engine
    {
        namespace types
        {

            struct compound_schema
            {
                std::string const_part;
                std::vector<std::string> variadic_part;
            };

            struct compound
            {
                std::string name;
                std::string symbol;
                struct compound_schema schema;
            };

            std::ostream& operator<<(std::ostream& os, const struct DecoderResult rhs);

            struct DecoderResult {
                time_t datetime;
                std::string result;
            };

            struct DecoderInput {
                std::string input;
            };

        }
    }
}
