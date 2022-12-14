
#include "include/HttpServer.hpp"
#include "spdlog/spdlog.h"

namespace decoder
{
    namespace http
    {

        void HttpServer::HandleConnection(pointer new_connection, const boost::system::error_code& error) {
            if (!error) {
                new_connection->Start();
            }
            StartAccept();
        }
        void HttpServer::StartAccept() {
            pointer new_connection = TcpConnection::Create((boost::asio::io_service&) server_acceptor.get_executor().context(), this->registry);

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

            #ifdef DEBUG_HTTPSERVER_MAKEREGISTRYENTRY

                std::string smethod;

                switch(reg.method) {
                    case request_method::GET:
                        smethod = "GET";
                        break;
                    case request_method::POST:
                        smethod = "POST";
                        break;
                    case request_method::PUT:
                        smethod = "PUT";
                        break;
                    case request_method::DELETE:
                        smethod = "DELETE";
                        break;
                    default:
                        break;
                }


                spdlog::get("console")->info("Created {} for {}", smethod, endpoint);
            #endif


            registry.push_back(reg);
        }

        HttpServer::HttpServer(boost::asio::io_context& ctx, short port) : port(port), server_acceptor(ctx, tcp::endpoint(tcp::v4(), port))
        {
            #ifdef DEBUG_HTTPSERVER_CONSTR
                spdlog::get("console")->get("Serving http server on port {}", port);
            #endif
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

        struct http_response Redirect(struct http_response res, std::string redirect_endpoint)  {
            res.code = response_code::MOVED;
            res.location = redirect_endpoint;
            return res;
        }

    }
}
