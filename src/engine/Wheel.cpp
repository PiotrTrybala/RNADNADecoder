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


            this->layersAmount = wheel["layersAmount"].get<int>();

            auto layers = wheel["layers"];
            int level = 1;

            std::vector<std::vector<std::string> > jsonLayers;

            for (auto& layer : layers) {
                std::vector<std::string> values = layer["values"].get<vector<std::string> >();
                jsonLayers.push_back(values);
            }



            // auto results = wheel["results"];
            // int resultIndex = 0;
            // for (auto& result : results) {
            //     std::cout << "Result #" << resultIndex++ << ": \n";
            //     std::cout << "Name: " << result["name"].get<std::string>() << "\n";
            //     std::cout << "Symbol: " << result["symbol"].get<std::string>() << "\n";
            //     std::cout << "Parents: " << result["parents"].get<int>() << "\n";
            // }


        }
    }
};
