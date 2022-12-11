#include "include/HttpServer.hpp"

namespace decoder
{
    namespace http
    {

        void HttpServer::handle_connection(TcpConnection::pointer new_connection, const boost::system::error_code& error) {

            if (!error) {
                new_connection->start();
            }
            start_accept();
        }
        void HttpServer::start_accept() {
            TcpConnection::pointer new_connection = TcpConnection::create((boost::asio::io_service&) server_acceptor.get_executor().context());

            server_acceptor.async_accept(new_connection->socket(), boost::bind(&HttpServer::handle_connection, this, new_connection, boost::placeholders::_1));
        }

        void HttpServer::make_registry_entry(RequestMethod method, std::string endpoint, endpoint_func& func) {
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

        HttpServer::HttpServer(short port) : port(port), server_acceptor(ios, tcp::endpoint(tcp::v4(), port))
        {
            start_accept();
        }
        HttpServer &HttpServer::operator=(const HttpServer &rhs)
        {
            if (this == &rhs) return *this;
            return *this;
        }
        HttpServer::~HttpServer()
        {
        }
        void HttpServer::request(std::string endpoint)
        {
        }
        void HttpServer::get(std::string endpoint, endpoint_func func)
        {
            make_registry_entry(RequestMethod::GET, endpoint, func);
        }
        void HttpServer::post(std::string endpoint, endpoint_func func)
        {
            make_registry_entry(RequestMethod::POST, endpoint, func);
        }
        void HttpServer::put(std::string endpoint, endpoint_func func)
        {
            make_registry_entry(RequestMethod::PUT, endpoint, func);
        }
        void HttpServer::del(std::string endpoint, endpoint_func func)
        {
            make_registry_entry(RequestMethod::DELETE, endpoint, func);
        }

        void HttpServer::redirect(std::string redirect_endpoint)
        {
        }
        void HttpServer::run()
        {
            ios.run();
        }
        void HttpServer::stop()
        {
            ios.stop();
        }

    }
}
