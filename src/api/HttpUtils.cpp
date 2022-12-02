#include "include/HttpUtils.hpp"

namespace decoder {
    namespace http {
        std::string Utils::trim(const std::string& s) {
            std::string out = "";
            for (int i = 0; i < s.length(); i++) if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n') out += s[i];
            return out;
        }
        std::vector<std::string> Utils::split(std::string& s, std::string& delim) {
            std::vector<std::string> out;
            size_t pos = 0;
            while((pos = s.find(delim)) != std::string::npos) {
                out.push_back(s.substr(0, pos));
                s.erase(0, pos + delim.length());
            }
            return out;
        }
    }
}
