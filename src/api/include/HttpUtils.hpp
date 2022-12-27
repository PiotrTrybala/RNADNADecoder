#pragma once

#include <vector>
#include <cstring>
#include <string>

namespace decoder {
    namespace http {

        class Utils {

            public:
                static std::string Trim(const std::string& s);
                static std::vector<std::string> Split(std::string& s, std::string delim);
        };

    }
}
