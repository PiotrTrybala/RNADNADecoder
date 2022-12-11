#include "HttpParser.hpp"
#include "HttpTypes.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
namespace decoder {
    namespace http {
        using boost::asio::ip::tcp;
        using endpoint_func = std::function<struct http_response(struct http_request& req)>;

        struct endpoint_reg {
            enum RequestMethod method;
            std::string endpoint;
            endpoint_func* func;
        };

        class HttpServer {
            private:

                const short DEFAULT_PORT = 3000;
                unsigned short port;

                std::vector<struct endpoint_reg> registry;

                void make_registry_entry(RequestMethod method, std::string endpoint, endpoint_func& func);


            public:

                HttpServer() = default;
                HttpServer(short port);
                HttpServer(const HttpServer& rhs);
                HttpServer& operator=(const HttpServer& rhs);
                ~HttpServer();

                void request(std::string endpoint);
                void response();
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
