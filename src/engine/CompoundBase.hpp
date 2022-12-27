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

            const struct compund& GetCompoundBySequence(const std::string& seq);
            struct compound_schema MakeCompoundSchema(const std::string&& raw_schema);
            void ParseSchema();

        public:

            CompoundBase(const std::string& filepath);
            ~CompoundBase();
            std::string GetSymbol(const std::string& seq);

        };
    }
}
