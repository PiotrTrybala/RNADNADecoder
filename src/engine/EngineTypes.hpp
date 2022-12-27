#pragma once

#include <vector>
#include <cstring>
#include <unordered_map>

namespace decoder
{
    namespace engine
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

    }
}
