#pragma once

#include <string>

#include "HttpUtils.hpp"
#include "HttpTypes.hpp"

namespace decoder {
    namespace http {
        class Parser {
            public:
                /**
                * @brief Parses raw HTTP request to struct http_request
                *
                * @param req raw HTTP request
                * @return struct http_request struct holding parsed infomations
                */
                static struct http_request ParseRequest(std::string& req);
                /**
                 * @brief Transforms struct http_response to raw HTTP response ready to be sent to receiver
                 *
                 * @param res struct holding informations
                 * @return std::string raw HTTP response
                 */
                static std::string PrepareResponse(struct http_response& res);
        };


    }

}
