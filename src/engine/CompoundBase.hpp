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
using decoder::engine::types::compound;
using decoder::engine::types::compound_schema;

namespace decoder
{
    namespace engine
    {
        class CompoundBase
        {
        private:

            struct compound start_compound;
            std::vector<struct compound> stop_compound;

            const struct compund& getCompoundBySequence(const std::string& seq);
            struct compound_schema& makeCompoundSchema(const std::string&& raw_schema);

            void ParseSchemaJSONFile();

            std::ifstream* compoundSchemaStream;

            std::unordered_map<std::string, struct compound> compoundSymbolLookup;

        public:

            CompoundBase(const std::string& filepath);
            ~CompoundBase();

            const std::string& getCompoundName(const std::string& seq);
            const std::string& getCompoundSymbol(const std::string& seq);
            const struct compound_schema& getCompoundSchema(const std::string& seq);

            const std::string& getSymbol(const std::string& seq);

        };
    }
}
