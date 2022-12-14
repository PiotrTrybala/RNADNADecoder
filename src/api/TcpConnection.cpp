#include "include/TcpConnection.hpp"
#include <iostream>

namespace decoder {
    namespace http {

        void TcpConnection::start() {
            boost::asio::async_read_until(socket_, request, "\r\n", boost::bind(&TcpConnection::handle_request, shared_from_this(), *this->registry, boost::placeholders::_1));
        }

        void TcpConnection::handle_request(v_reg& reg, const boost::system::error_code&) {
            std::cout << "reg handle: " << &reg << std::endl;
            std::istream is{&request};
            std::stringstream ss; ss << is.rdbuf();
            std::string piped_request = ss.str();

            std::cout << "chrome req: " << piped_request << "\n";

            struct http_request req = Parser::ParseRequest(piped_request);
            struct http_response res;
            endpoint_func func;

            std::cout << "1\n";

            std::cout << "size of regs: " << reg.size() << "\n";

            for (endpoint_reg r : reg) {
                std::cout << "endpoint: " << r.endpoint << "\n";
                if (r.method == req.method && r.endpoint == req.path) {
                    std::cout << "path: " << r.endpoint << ", " << r.func << std::endl;
                    func = *r.func; break;
                }
            }
            res = func(res, req);
            std::string prepared_response = Parser::PrepareResponse(res);
            std::cout << prepared_response << "\n";
            boost::asio::async_write(socket_, boost::asio::buffer(prepared_response), boost::bind(&TcpConnection::handle_response, shared_from_this(), res, boost::placeholders::_1));

        }

        void TcpConnection::handle_response(struct http_response& res, const boost::system::error_code&) {}
    }
}
