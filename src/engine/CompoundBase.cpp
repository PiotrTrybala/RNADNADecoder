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
            std::cout << "parsing 1\n";
            json allSchema = json::parse(*this->compoundSchemaStream);
            std::cout << "parsing 2\n";
            json specialCompounds = allSchema["special"];
            json startingCompounds = specialCompounds["start"];
            std::cout << "parsing 3\n";
            for (auto start : startingCompounds) {
                struct compound compound;
                compound.name = start["name"].get<std::string>();
                compound.symbol = start["symbol"].get<std::string>();
                compound.schema = makeCompoundSchema(start["schema"].get<std::string>());
                start_compound = compound;
                std::cout << "parsing 4\n";



                this->compoundSymbolLookup.insert({compound.schema.const_part, compound}); // TODO: fix and add variadic part to add
            }
            std::cout << "parsing 5\n";
            json stopppingCompounds = specialCompounds["stop"];
            std::cout << "parsing 6\n";
            for (auto stop : stopppingCompounds) {
                std::cout << "parsing 7\n";
                struct compound compound;
                compound.name = stop["name"].get<std::string>();
                compound.symbol = stop["symbol"].get<std::string>();
                compound.schema = makeCompoundSchema(stop["schema"].get<std::string>());

                for (const std::string& c : compound.schema.variadic_part) {
                    this->compoundSymbolLookup.insert({compound.schema.const_part + c, compound});
                }

                stop_compound.emplace_back(compound);
            }
            std::cout << "parsing 8\n";
            json restCompounds = allSchema["compounds"];
            std::cout << "parsing 9\n";
            for (auto comp : restCompounds) {
                std::cout << "parsing 10\n";
                struct compound compound;
                compound.name = comp["name"].get<std::string>();
                compound.symbol = comp["symbol"].get<std::string>();
                compound.schema = makeCompoundSchema(comp["schema"].get<std::string>());

                for (int i = 0; i < compound.schema.variadic_part.size(); i++) {
                    std::cout << "parsing 11\n";
                    std::string lookup {compound.schema.const_part};
                    lookup += compound.schema.variadic_part[i];
                    this->compoundSymbolLookup.insert({lookup, compound});
                }
            }

        }

        auto CompoundBase::makeCompoundSchema(const std::string&& raw_schema) -> struct compound_schema {
            std::cout << "make 1\n";
            struct compound_schema schema;
            int i = 0;
            while(raw_schema[i] != '[' && i < raw_schema.length()) {
                std::cout << i << "1: " << raw_schema[i] << "\n";
                schema.const_part += raw_schema[i];
                i++;
            }
            i++;
            while(raw_schema[i] != ']' && i < raw_schema.length()) {
                std::cout << i << "2: " << raw_schema[i] << "\n";
                std::string variadic {raw_schema[i]};
                schema.variadic_part.emplace_back(variadic);
                i++;
            }

            std::cout << "schema const part: " << schema.const_part << "\n";
            for (int i = 0; i < schema.variadic_part.size(); i++) {
                std::cout << "variadic index part " << i << ": " << schema.variadic_part[i] << "\n";
            }

            return schema;
        }

        auto CompoundBase::getCompoundName(const std::string &seq) -> const std::string&
        {
        }
        auto CompoundBase::getCompoundSymbol(const std::string &seq) -> const std::string&
        {
        }
        auto CompoundBase::getCompoundSchema(const std::string &seq) -> const struct compound_schema&
        {
        }

        auto CompoundBase::getSymbol(const std::string &seq) -> std::string
        {
            if (this->compoundSymbolLookup.find(seq) == compoundSymbolLookup.end()) {
                std::string error {"error"};
                return error;
            }
            return this->compoundSymbolLookup[seq].symbol;
        }

    }
}
