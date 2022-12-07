#pragma once
#include <string>
#include "nlohmann/json.hpp"
#include <vector>

namespace decoder {
    namespace http {

        enum class ResponseCode {
            OK = 200,
            NOTFOUND = 404,
            REDIRECT = 302,
            MOVED = 301,
            INTERNALERROR = 501
        };

        enum class RequestMethod {
            GET,
            POST,
            PUT,
            DELETE
        };

        enum class AcceptTypes {
            TEXTPLAIN,
            APPLICATIONJSON,
            TEXTHTML,
            TEXTXML
        };

        enum class CharsetTypes {
            UTF8
        };

        enum class AcceptLanguage {
            PL,
            ENUS
        };

        enum class ConnectionState {
            CLOSE,
            KEEPALIVE
        };

        enum class TransferEncodings {
            CHUNKED,
            IDENTITY,
            GZIP,
            COMPRESS
        };

        enum class CacheControls {
            NOSTORE,
            NOCACHE,
            MAXAGE,
            MINFRESH
        };

        enum class AuthScheme {
            BASIC,
            BEARER,
            DIGEST
        };

        struct Authorization {
            enum AuthScheme scheme;
            std::string authParams;
        };

        struct http_request {

            enum RequestMethod method;
            std::string path;
            std::string version = "HTTP/1.1";

            std::string host;
            std::string user_agent;
            std::vector<enum AcceptTypes> accepts;
            std::vector<enum CharsetTypes> charsets;
            std::vector<enum AcceptLanguage> languages;
            enum TransferEncodings encoding;
            struct Authorization auth;

            int contentLength;

            int keepAlive;
            enum ConnectionState connection;
            std::string trailing = "\r\n";

            nlohmann::json js_body;
            std::string url_encoded_body;
        };

        struct http_response {

            std::string version = "HTTP/1.1";
            enum ResponseCode code;
            std::string server;

            std::string location;

            std::vector<enum CacheControls> cache;

            enum ConnectionState connection;
            std::string trailing = "\r\n";
        };


    }
}
