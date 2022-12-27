#pragma once

#include <string>
#include <vector>

#include "nlohmann/json.hpp"

namespace decoder {
    namespace http {

        using endpoint_function = std::function<struct http_response(struct http_response&, struct http_request&)>;

        enum class response_code {
            OK = 200,
            NOTFOUND = 404,
            REDIRECT = 302,
            MOVED = 301,
            INTERNALERROR = 500,
            BADREQUEST = 400,
            NONE = -1
        };

        enum class request_method {
            GET,
            POST,
            PUT,
            DELETE
        };

        enum class accept_type {
            TEXTPLAIN,
            APPLICATIONJSON,
            TEXTHTML,
            TEXTXML
        };

        enum class charset_type {
            UTF8
        };

        enum class accept_language {
            PL,
            ENUS
        };

        enum class connection_state {
            CLOSE,
            KEEPALIVE,
            NONE
        };

        enum class transfer_encoding {
            CHUNKED,
            IDENTITY,
            GZIP,
            COMPRESS,
            NONE
        };

        enum class cache_control {
            NOSTORE,
            NOCACHE,
            MAXAGE,
            MINFRESH,
            NONE
        };

        enum class auth_scheme {
            BASIC,
            BEARER,
            DIGEST,
            NONE
        };

        enum class cors {
            ALL,
            NONE,
            SELECT
        };

        struct endpoint_reg {
            enum request_method method;
            std::string endpoint;
            endpoint_function* func;
        };

        struct authorization {
            enum auth_scheme scheme;
            std::string authParams;
        };

        struct http_request {

            enum request_method method;
            std::string path = "";
            std::string version = "HTTP/1.1";

            std::string host = "";
            std::string user_agent = "";
            std::vector<enum accept_type> accepts;
            std::vector<enum charset_type> charsets;
            std::vector<enum accept_language> languages;
            enum transfer_encoding encoding = transfer_encoding::NONE;
            struct authorization auth;

            int contentLength;

            int keepAlive = -1;
            enum connection_state connection = connection_state::NONE;
            std::string trailing = "\r\n";

            nlohmann::json js_body;
            std::string url_encoded_body = "";
        };



        struct http_response {

            std::string version = "HTTP/1.1";
            enum response_code code = response_code::NONE;
            std::string server = "";

            std::string location = "";

            std::vector<enum cache_control> cache;

            enum connection_state connection = connection_state::NONE;

            enum cors corsMode = cors::NONE;
            std::string corsAllow = "";

            std::string trailing = "\r\n";

            nlohmann::json body;
        };


    }
}
