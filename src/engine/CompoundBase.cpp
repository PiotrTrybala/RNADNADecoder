#include "CompoundBase.hpp"
#include <iostream>
namespace decoder
{
    namespace engine
    {

        CompoundBase::CompoundBase(const std::string &filepath)
        {
            this->compoundSchemaStream = new std::ifstream(filepath);
            this->ParseSchemaJSONFile();
        }
        CompoundBase::~CompoundBase()
        {
            this->compoundSchemaStream->close();
            delete this->compoundSchemaStream;
        }

        void CompoundBase::ParseSchemaJSONFile() {
            json allSchema = json::parse(*this->compoundSchemaStream);
            json specialCompounds = allSchema["special"];
            json startingCompounds = specialCompounds["start"];
            for (auto start : startingCompounds) {
                struct compound compound;
                compound.name = start["name"].get<std::string>();
                compound.symbol = start["symbol"].get<std::string>();
                compound.schema = makeCompoundSchema(start["schema"].get<std::string>());
                start_compound = compound;

                this->compoundSymbolLookup.insert({compound.schema.const_part, compound}); // TODO(piotrek): fix and add variadic part to add
            }
            json stopppingCompounds = specialCompounds["stop"];
            for (auto stop : stopppingCompounds) {
                struct compound compound;

                compound.name = stop["name"].get<std::string>();
                compound.symbol = stop["symbol"].get<std::string>();
                compound.schema = makeCompoundSchema(stop["schema"].get<std::string>());

                this->compoundSymbolLookup[compound.schema.const_part] = compound;
                stop_compound.emplace_back(compound);
            }

            json restCompounds = allSchema["compounds"];
            for (auto comp : restCompounds) {
                struct compound compound;
                compound.name = comp["name"].get<std::string>();
                compound.symbol = comp["symbol"].get<std::string>();
                compound.schema = makeCompoundSchema(comp["schema"].get<std::string>());

                for (int i = 0; i < compound.schema.variadic_part.size(); i++) {
                    std::string lookup {compound.schema.const_part};
                    lookup += compound.schema.variadic_part[i];
                    this->compoundSymbolLookup.insert({lookup, compound});
                }
            }
        }

        auto CompoundBase::makeCompoundSchema(const std::string&& raw_schema) -> struct compound_schema {
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

        auto CompoundBase::getCompoundName(const std::string &seq) -> const std::string&
        {
            return this->compoundSymbolLookup[seq].name;
        }
        auto CompoundBase::getCompoundSymbol(const std::string &seq) -> const std::string&
        {
            return this->compoundSymbolLookup[seq].symbol;
        }
        auto CompoundBase::getCompoundSchema(const std::string &seq) -> const struct compound_schema&
        {
            return this->compoundSymbolLookup[seq].schema;
        }

        auto CompoundBase::getSymbol(const std::string &seq) -> std::string
        {
            if (this->compoundSymbolLookup.find(seq) == compoundSymbolLookup.end()) {
                std::string error {""};
                return error;
            }
            return this->compoundSymbolLookup[seq].symbol;
        }

    }
}
