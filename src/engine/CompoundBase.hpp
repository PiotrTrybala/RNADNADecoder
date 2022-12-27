#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <cctype>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include <fstream>

#include "EngineTypes.hpp"

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

            const struct compund& GetCompoundBySequence(const std::string& seq);
            struct compound_schema MakeCompoundSchema(const std::string&& raw_schema);

            void ParseSchema();

            std::ifstream* compound_schema_stream;

            std::unordered_map<std::string, struct compound> compound_symbol_lookup;

        public:

            CompoundBase(const std::string& filepath);
            ~CompoundBase();
            std::string getSymbol(const std::string& seq);

        };
    }
}
