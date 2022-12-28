#pragma once

#include <vector>
#include <string>
#include <cctype>
#include <cstring>
#include <fstream>
#include <unordered_map>

#include "EngineTypes.hpp"
#include "nlohmann/json.hpp"

using nlohmann::json;

namespace decoder
{
    namespace engine
    {
        class CompoundBase
        {
        private:

            struct compound start_compound;
            std::vector<struct compound> stop_compound;
            std::ifstream* compound_schema_stream;
            std::unordered_map<std::string, struct compound> compound_symbol_lookup;

            /**
             * @brief Parses raw schema into struct compound_schema
             *
             * @param raw_schema raw schema from file
             * @return struct compound_schema parsed schema into const part and variadic part
             */
            struct compound_schema MakeCompoundSchema(const std::string&& raw_schema);

            /**
             * @brief Parses schema file in JSON format
             *
             */
            void ParseSchema();

        public:
            /**
             * @brief Construct a new Compound Base object
             *
             * @param filepath path to JSON file storing schema
             */
            CompoundBase(const std::string& filepath);
            ~CompoundBase();
            /**
             * @brief Gets symbol for specified compound sequence
             *
             * @param seq compound
             * @return std::string symbol related to given compound
             */
            std::string GetSymbol(const std::string& seq);

        };
    }
}
