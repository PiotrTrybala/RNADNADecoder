#include "CompoundBase.hpp"

namespace decoder
{
    namespace engine
    {

        CompoundBase::CompoundBase(const std::string &filepath)
        {
            this->compoundSchemaStream = new std::ifstream(std::move(filepath));
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
            }
            json stopppingCompounds = specialCompounds["stop"];
            for (auto stop : stopppingCompounds) {
                struct compound compound;
                compound.name = stop["name"].get<std::string>();
                compound.symbol = stop["symbol"].get<std::string>();
                compound.schema = makeCompoundSchema(stop["schema"].get<std::string>());

                stop_compound.push_back(compound);
            }
            json restCompounds = allSchema["compounds"];
            for (auto comp : restCompounds) {
                struct compound compound;
                compound.name = comp["name"].get<std::string>();
                compound.symbol = comp["symbol"].get<std::string>();
                compound.schema = makeCompoundSchema(comp["schema"].get<std::string>());
                for (std::string c : compound.schema.variadic_part) {
                    this->compoundSymbolLookup.insert({compound.schema.const_part + c, compound});
                }
            }

        }

        struct compound_schema& CompoundBase::makeCompoundSchema(const std::string&& raw_schema) {
            std::string raw = std::move(raw_schema);
            struct compound_schema schema;
            char schemaElem;
            int i = 0;
            while((schemaElem = raw[i]) != '[') {
                schema.const_part += schemaElem;
                i++;
            }
            while((schemaElem = raw[i]) != ']') {
                schema.variadic_part.push_back("" + schemaElem);
            }
            return schema;
        }

        const std::string &CompoundBase::getCompoundName(const std::string &seq)
        {
        }
        const std::string &CompoundBase::getCompoundSymbol(const std::string &seq)
        {
        }
        const struct compound_schema &CompoundBase::getCompoundSchema(const std::string &seq)
        {
        }

        const std::string &CompoundBase::getSymbol(const std::string &seq)
        {
        }

    }
}
