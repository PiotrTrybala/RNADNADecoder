#pragma once

#include <string>

#include "HttpUtils.hpp"
#include "HttpTypes.hpp"

namespace decoder {
    namespace http {
        class Parser {
            public:
                static struct http_request ParseRequest(std::string& req);
                static std::string PrepareResponse(struct http_response& res);
        };


    }

}
