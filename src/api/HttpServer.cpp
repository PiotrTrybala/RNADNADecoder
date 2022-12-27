#include "include/HttpServer.hpp"
#include <iostream>
namespace decoder
{
    namespace http
    {

        void HttpServer::HandleConnection(decoder::http::pointer new_connection, const boost::system::error_code& error) {
            if (!error) {
                new_connection->Start();
            }
            StartAccept();
        }
        void HttpServer::StartAccept() {
            decoder::http::pointer new_connection = TcpConnection::Create((boost::asio::io_service&) server_acceptor.get_executor().context(), this->registry);

            server_acceptor.async_accept(new_connection->GetSocket(), boost::bind(&HttpServer::HandleConnection, this, new_connection, boost::placeholders::_1));
        }

        void HttpServer::MakeRegistryEntry(request_method method, std::string endpoint, endpoint_function& func) {
            struct endpoint_reg reg;
            reg.method = method;
            reg.endpoint = endpoint;
            reg.func = &func;
            for (auto& it : registry) {
                if (it.endpoint == reg.endpoint && reg.method == it.method) {
                    it.func = &func;
                    return;
                }
            }
            registry.push_back(reg);
        }

        HttpServer::HttpServer(boost::asio::io_context& ctx, short port) : port(port), server_acceptor(ctx, tcp::endpoint(tcp::v4(), port))
        {
            StartAccept();
        }
        HttpServer &HttpServer::operator=(const HttpServer &rhs)
        {
            if (this == &rhs) return *this;
            return *this;
        }
        HttpServer::~HttpServer()
        {
        }
        void HttpServer::Get(std::string endpoint, endpoint_function func)
        {
            MakeRegistryEntry(request_method::GET, std::move(endpoint), func);
        }
        void HttpServer::Post(std::string endpoint, endpoint_function func)
        {
            MakeRegistryEntry(request_method::POST, std::move(endpoint), func);
        }
        void HttpServer::Put(std::string endpoint, endpoint_function func)
        {
            MakeRegistryEntry(request_method::PUT, std::move(endpoint), func);
        }
        void HttpServer::Del(std::string endpoint, endpoint_function func)
        {
            MakeRegistryEntry(request_method::DELETE, std::move(endpoint), func);
        }

        void HttpServer::Redirect(std::string redirect_endpoint)
        {
        }
        void HttpServer::Run()
        {
            // ios.run();
        }
        void HttpServer::Stop()
        {
            // ios.stop();
        }

    }
}
