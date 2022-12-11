#include "include/HttpServer.hpp"

namespace decoder
{
    namespace http
    {

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

        HttpServer::HttpServer(short port) : port(port), server_acceptor(ios)
        {

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
        }
        void HttpServer::post(std::string endpoint, endpoint_func func)
        {
        }
        void HttpServer::put(std::string endpoint, endpoint_func func)
        {
        }
        void HttpServer::del(std::string endpoint, endpoint_func func)
        {
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
