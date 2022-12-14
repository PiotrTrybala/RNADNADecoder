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

            std::cout << "path: " << req.path << "\n";
            std::cout << "user-agent: " << req.user_agent << "\n";
            std::cout << req.js_body.get<std::string>() << "\n";

        }

        void TcpConnection::handle_response(const boost::system::error_code&) {

        }
    }
}
