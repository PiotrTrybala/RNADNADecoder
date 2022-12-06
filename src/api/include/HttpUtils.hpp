#pragma once
#include <vector>
#include <cstring>
#include <string>

namespace decoder {
    namespace http {

        class Utils {

            public:
                static std::string trim(const std::string& s);
                static std::vector<std::string> split(std::string& s, std::string delim);
        };

    }
}
