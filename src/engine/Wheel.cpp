#include "Wheel.hpp"

namespace decoder
{
    namespace wheel
    {
        Wheel::Wheel(const std::string& filepath)
        {
            this->ParseWheelFile(filepath);
        }
        Wheel::~Wheel()
        {
            delete this->wheelRep;
        }

        auto Wheel::GetCompound(const std::string& seq) -> char
        {
            struct ResultNode<char> result = this->GetCompoundBody(seq);
            return result.value;
        }
        auto Wheel::GetCompoundBody(const std::string& seq) -> struct ResultNode<char>
        {
            return {};
        }

        void Wheel::ParseWheelFile(const std::string& filepath) {

            this->wheelRep = new std::ifstream(filepath);

            using json = nlohmann::json;

            json wheel = json::parse(*this->wheelRep);

            std::cout << "Layers amount: " << wheel["layersAmount"] << "\n";
        }
    }
};
