#include "include/TcpConnection.hpp"
#include "spdlog/spdlog.h"

namespace decoder {
    namespace http {

        void TcpConnection::Start() {
            boost::asio::async_read_until(socket, request, "\r\n", boost::bind(&TcpConnection::HandleRequest, shared_from_this(), *this->regstry, boost::placeholders::_1));
        }

        void TcpConnection::HandleRequest(decoder::http::registry& reg, const boost::system::error_code&) {
            std::istream is{&request};
            std::stringstream ss; ss << is.rdbuf();
            std::string piped_request = ss.str();

            #ifdef DEBUG_TCPCONNECTION_HANDLEREQUEST
                spdlog::get("console")->info("Got request: {}", piped_request);
            #endif

            struct http_request req = Parser::ParseRequest(piped_request);
            struct http_response res;
            endpoint_function func;
            bool endpoint_found = false;

            for (struct endpoint_reg r : reg) {
                if (r.method == req.method && r.endpoint == req.path) {
                    endpoint_found = true;
                    func = *r.func; break;
                }
            }

            if (!endpoint_found) {
                #ifdef DEBUG_TCPCONNECTION_HANDLEREQUEST
                    spdlog::get("console")->info("Endpoint was not found: {}", req.path);
                #endif
                res.code = response_code::NOTFOUND;
                res.body = R"({"response": "endpoint could not be found"})";
            } else {
                res = func(res, req);
            }
            std::string prepared_response = Parser::PrepareResponse(res);
            boost::asio::async_write(socket, boost::asio::buffer(prepared_response), boost::bind(&TcpConnection::HandleResponse, shared_from_this(), res, boost::placeholders::_1));
        }

        void TcpConnection::HandleResponse(struct http_response& res, const boost::system::error_code&) {}
    }
}
