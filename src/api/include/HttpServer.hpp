#include "HttpParser.hpp"
#include "HttpTypes.hpp"
namespace decoder {
    namespace http {

        using endpoint_func = std::function<struct http_response(struct http_request& req)>;

        class HttpServer {
            private:

                Parser* parser;
                const short DEFAULT_PORT = 3000;

            public:

                HttpServer() = default;
                HttpServer(short port);
                HttpServer(const HttpServer& rhs);
                HttpServer& operator=(const HttpServer& rhs);
                ~HttpServer();

                void get(std::string endpoint, endpoint_func func);
                void post(std::string endpoint, endpoint_func func);
                void put(std::string endpoint, endpoint_func func);
                void del(std::string endpoint, endpoint_func func);

                void redirect(std::string redirect_endpoint);
                void run();
                void stop();

        };

    }
}
