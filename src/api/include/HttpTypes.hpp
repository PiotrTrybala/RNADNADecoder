#pragma once
#include <string>
#include "nlohmann/json.hpp"
#include <vector>

namespace decoder {
    namespace http {

        using EndpointFunction = std::function<struct HttpResponse(struct HttpResponse&, struct HttpRequest&)>;

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

        enum class AcceptType {
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

        enum class TransferEncoding {
            CHUNKED,
            IDENTITY,
            GZIP,
            COMPRESS,
            NONE
        };

        enum class CacheControl {
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

        struct EndpointReg {
            enum RequestMethod method;
            std::string endpoint;
            EndpointFunction* func;
        };

        struct Authorization {
            enum AuthScheme scheme;
            std::string authParams;
        };

        struct HttpRequest {

            enum RequestMethod method;
            std::string path = "";
            std::string version = "HTTP/1.1";

            std::string host = "";
            std::string user_agent = "";
            std::vector<enum AcceptType> accepts;
            std::vector<enum CharsetTypes> charsets;
            std::vector<enum AcceptLanguage> languages;
            enum TransferEncoding encoding = TransferEncoding::NONE;
            struct Authorization auth;

            int contentLength;

            int keepAlive = -1;
            enum ConnectionState connection = ConnectionState::NONE;
            std::string trailing = "\r\n";

            nlohmann::json js_body;
            std::string url_encoded_body = "";
        };



        struct HttpResponse {

            std::string version = "HTTP/1.1";
            enum ResponseCode code = ResponseCode::NONE;
            std::string server = "";

            std::string location = "";

            std::vector<enum CacheControl> cache;

            enum ConnectionState connection = ConnectionState::NONE;

            enum CORS corsMode = CORS::NONE;
            std::string corsAllow = "";

            std::string trailing = "\r\n";

            nlohmann::json body;
        };


    }
}
