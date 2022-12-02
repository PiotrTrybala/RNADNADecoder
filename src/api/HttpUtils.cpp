#include "HttpUtils.hpp"

namespace decoder {
    namespace http {

        std::string Utils::trim(const std::string& s) {
            std::string out = "";
            for (int i = 0; i < s.length(); i++) if (s[i] != ' ') out += s[i];
            return out;

        }
        std::vector<std::string> Utils::split(std::string& s, std::string& delim) {

        }

    }
}
