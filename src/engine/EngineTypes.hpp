#pragma once

#include <vector>
#include <cstring>
#include <unordered_map>

namespace decoder
{
    namespace engine
    {
        /**
         * @brief struct compound_schema unparsed representation of compound
         *
         * @param const_part part in compound which is not changing in group of compounds
         * @param variadic_part part of compound which is different depending of compound in group
         *
         */
        struct compound_schema
        {
            std::string const_part;
            std::vector<std::string> variadic_part;
        };

        /**
         * @brief struct compound parsed representation
         *
         * @param name name of parsed compound (Syr, ...)
         * @param symbol symbol of parsed compound (K, L, M, ...)
         * @param schema group of 3 letters which identifies the compound
         */
        struct compound
        {
            std::string name;
            std::string symbol;
            struct compound_schema schema;
        };

    }
}
