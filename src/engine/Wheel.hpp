#include <cstring>
#include <iostream>
#include <memory>
#include <cctype>
#include <cstdlib>
#include <fstream>

#include "WheelTypes.hpp"

#include <nlohmann/json.hpp>

namespace decoder {
    namespace wheel {
        class Wheel {
            private:

                unsigned int layersAmount;
                unsigned int resultsAmount;

                vector<Layer<char> > layers;
                vector<ResultNode <char> > results;

                std::ifstream* wheelRep;

            public:
                Wheel(const std::string& filepath);
                ~Wheel();

                void ParseWheelFile(const std::string& filepath);

                char GetCompound(const std::string& seq);
                struct ResultNode<char> GetCompoundBody(const std::string& seq);

        };
    }
}
