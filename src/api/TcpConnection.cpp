#include "include/TcpConnection.hpp"
#include <iostream>

namespace decoder {
    namespace http {

        void TcpConnection::start() {
            boost::asio::async_read_until(socket_, request, "\r\n", boost::bind(&TcpConnection::handle_request, shared_from_this(), boost::placeholders::_1));
        }

        void TcpConnection::handle_request(const boost::system::error_code&) {

            std::istream is{&request};
            std::stringstream ss; ss << is.rdbuf();
            std::string piped_request = ss.str();
            struct http_request req = Parser::ParseRequest(piped_request);

            struct http_response res;
            endpoint_func func;

            for (endpoint_reg& reg : this->registry) {
                if (reg.method == req.method && req.path == req.path) {
                    func = *reg.func; break;
                }
            }

            res = func(res, req);

            std::string prepared_response = Parser::PrepareResponse(res);

            boost::asio::async_write(socket_, boost::asio::buffer(prepared_response), boost::bind(&TcpConnection::handle_response, shared_from_this(), res, boost::placeholders::_1));

        }

        void TcpConnection::handle_response(struct http_response& res, const boost::system::error_code&) {}
    }
}
