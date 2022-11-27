#include <cstring>
#include <iostream>
#include <memory>
#include <cctype>
#include <cstdlib>
#include <fstream>

#include "WheelTypes.hpp"

#include "json.hpp"

namespace Decoder {
    namespace Wheel {
        template<class T>
        class Wheel {
            private:

                unsigned int layers;
                unsigned int results;

                vector<Layer<char> > layers;

                std::ifstream* wheelRep;


            public:
                Wheel(std::string filepath);
                ~Wheel();


                char getCompound(string seq);
                struct ResultNode<char> getCompoundBody(string seq);




        };
    }
}
