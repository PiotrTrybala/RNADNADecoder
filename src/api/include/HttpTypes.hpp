#pragma once
#include <string>
#include "nlohmann/json.hpp"
#include <vector>

namespace decoder {
    namespace http {

        using endpoint_func = std::function<struct http_response(struct http_response&, struct http_request&)>;

        enum class ResponseCode {
            OK = 200,
            NOTFOUND = 404,
            REDIRECT = 302,
            MOVED = 301,
            INTERNALERROR = 500,
            BADREQUEST = 400,
            NONE = -1
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
            KEEPALIVE,
            NONE
        };

        enum class TransferEncodings {
            CHUNKED,
            IDENTITY,
            GZIP,
            COMPRESS,
            NONE
        };

        enum class CacheControls {
            NOSTORE,
            NOCACHE,
            MAXAGE,
            MINFRESH,
            NONE
        };

        enum class AuthScheme {
            BASIC,
            BEARER,
            DIGEST,
            NONE
        };

        enum class CORS {
            ALL,
            NONE,
            SELECT
        };

        struct endpoint_reg {
            enum RequestMethod method;
            std::string endpoint;
            endpoint_func* func;
        };

        struct Authorization {
            enum AuthScheme scheme;
            std::string authParams;
        };

        struct http_request {

            enum RequestMethod method;
            std::string path = "";
            std::string version = "HTTP/1.1";

            std::string host = "";
            std::string user_agent = "";
            std::vector<enum AcceptTypes> accepts;
            std::vector<enum CharsetTypes> charsets;
            std::vector<enum AcceptLanguage> languages;
            enum TransferEncodings encoding = TransferEncodings::NONE;
            struct Authorization auth;

            int contentLength;

            int keepAlive = -1;
            enum ConnectionState connection = ConnectionState::NONE;
            std::string trailing = "\r\n";

            nlohmann::json js_body;
            std::string url_encoded_body = "";
        };



        struct http_response {

            std::string version = "HTTP/1.1";
            enum ResponseCode code = ResponseCode::NONE;
            std::string server = "";

            std::string location = "";

            std::vector<enum CacheControls> cache;

            enum ConnectionState connection = ConnectionState::NONE;

            enum CORS corsMode = CORS::NONE;
            std::string corsAllow = "";

            std::string trailing = "\r\n";

            nlohmann::json body;
        };


    }
}
