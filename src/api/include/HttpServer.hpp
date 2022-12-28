#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "HttpParser.hpp"
#include "HttpTypes.hpp"
#include "TcpConnection.hpp"

#define DEFAULT_PORT 3000
namespace decoder {
    namespace http {
        using boost::asio::ip::tcp;
        class HttpServer {
            private:
                unsigned short port;
                tcp::acceptor server_acceptor;
                std::vector<struct endpoint_reg> registry;
                using pointer = boost::shared_ptr<TcpConnection>;

                void MakeRegistryEntry(request_method method, std::string endpoint, endpoint_function& func);
                void HandleConnection(pointer new_connection, const boost::system::error_code& error);
                void StartAccept();
            public:

                HttpServer() = default;
                HttpServer(boost::asio::io_context& ctx, short port);
                HttpServer(const HttpServer& rhs);
                HttpServer& operator=(const HttpServer& rhs);
                ~HttpServer();

                void Get(std::string endpoint, endpoint_function func);
                void Post(std::string endpoint, endpoint_function func);
                void Put(std::string endpoint, endpoint_function func);
                void Del(std::string endpoint, endpoint_function func);

                void Redirect(std::string redirect_endpoint);
                void Run();
                void Stop();

        };

    }
}
