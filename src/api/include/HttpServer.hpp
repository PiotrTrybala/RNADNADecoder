#include "HttpParser.hpp"
#include "HttpTypes.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "TcpConnection.hpp"
namespace decoder {
    namespace http {
        using boost::asio::ip::tcp;

        class HttpServer {
            private:

                const short DEFAULT_PORT = 3000;
                unsigned short port;

                std::vector<struct endpoint_reg> registry;

                void make_registry_entry(RequestMethod method, std::string endpoint, endpoint_func& func);

                tcp::acceptor server_acceptor;
                // boost::asio::io_context ios;

                void handle_connection(TcpConnection::pointer new_connection, const boost::system::error_code& error);
                void start_accept();


            public:

                HttpServer() = default;
                HttpServer(boost::asio::io_context& ctx, short port);
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
