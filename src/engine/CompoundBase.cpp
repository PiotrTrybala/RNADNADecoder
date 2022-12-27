#include <iostream>

#include "CompoundBase.hpp"

namespace decoder
{
    namespace engine
    {

        CompoundBase::CompoundBase(const std::string &filepath)
        {
            this->compound_schema_stream = new std::ifstream(filepath);
            this->ParseSchema();
        }
        CompoundBase::~CompoundBase()
        {
            this->compound_schema_stream->close();
            delete this->compound_schema_stream;
        }

        void CompoundBase::ParseSchema() {
            json all_schema = json::parse(*this->compound_schema_stream);
            json special_compounds = all_schema["special"];
            json starting_compounds = special_compounds["start"];
            for (auto start : starting_compounds) {
                struct compound compound;
                compound.name = start["name"].get<std::string>();
                compound.symbol = start["symbol"].get<std::string>();
                compound.schema = MakeCompoundSchema(start["schema"].get<std::string>());
                start_compound = compound;

                this->compound_symbol_lookup.insert({compound.schema.const_part, compound}); // TODO(piotrek): fix and add variadic part to add
            }
            json stoppping_compounds = special_compounds["stop"];
            for (auto stop : stoppping_compounds) {
                struct compound compound;

                compound.name = stop["name"].get<std::string>();
                compound.symbol = stop["symbol"].get<std::string>();
                compound.schema = MakeCompoundSchema(stop["schema"].get<std::string>());

                this->compound_symbol_lookup[compound.schema.const_part] = compound;
                stop_compound.emplace_back(compound);
            }

            json rest_compounds = all_schema["compounds"];
            for (auto comp : rest_compounds) {
                struct compound compound;
                compound.name = comp["name"].get<std::string>();
                compound.symbol = comp["symbol"].get<std::string>();
                compound.schema = MakeCompoundSchema(comp["schema"].get<std::string>());

                for (int i = 0; i < compound.schema.variadic_part.size(); i++) {
                    std::string lookup {compound.schema.const_part};
                    lookup += compound.schema.variadic_part[i];
                    this->compound_symbol_lookup.insert({lookup, compound});
                }
            }
        }

        auto CompoundBase::MakeCompoundSchema(const std::string&& raw_schema) -> struct compound_schema {
            struct compound_schema schema;
            int i = 0;
            while(raw_schema[i] != '[' && i < raw_schema.length()) {
                schema.const_part += raw_schema[i];
                i++;
            }
            i++;
            while(raw_schema[i] != ']' && i < raw_schema.length()) {
                std::string variadic {raw_schema[i]};
                schema.variadic_part.emplace_back(variadic);
                i++;
            }
            return schema;
        }

        auto CompoundBase::GetSymbol(const std::string &seq) -> std::string
        {
            if (this->compound_symbol_lookup.find(seq) == compound_symbol_lookup.end()) {
                std::string error {""};
                return error;
            }
            return this->compound_symbol_lookup[seq].symbol;
        }

    }
}
