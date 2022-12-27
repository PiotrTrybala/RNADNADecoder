#include "include/HttpUtils.hpp"
#include <iostream>

namespace decoder {
    namespace http {
        std::string Utils::Trim(const std::string& s) {
            std::string out = "";
            for (char c : s) if (c != ' ' && c != '\t' && c != '\n') out += c;
            return out;
        }
        std::vector<std::string> Utils::Split(std::string& s, std::string delim) {
            std::vector<std::string> out;
            size_t pos = 0;
            while((pos = s.find(delim)) != std::string::npos) {
                out.push_back(s.substr(0, pos));
                s.erase(0, pos + delim.length());
            }
            out.push_back(s);
            return out;
        }
    }
}
