#include "include/HttpParser.hpp"
#include <iostream>

namespace decoder
{
    namespace http
    {
        auto Parser::ParseRequest(std::string &req) -> struct http_request
        {

            struct http_request request;

            std::string crlf = "\r\n";

            std::string http_body{};

            std::vector<std::string> http_lines = Utils::Split(req, crlf);
            std::vector<std::string> method_header = Utils::Split(http_lines[0], " ");

            std::string method = method_header[0];
            std::string path = method_header[1];
            std::string version = method_header[2]; // :)

            if (method == "GET")
            {
                request.method = request_method::GET;
            }
            else if (method == "POST")
            {
                request.method = request_method::POST;
            }
            else if (method == "PUT")
            {
                request.method = request_method::PUT;
            }
            else if (method == "DELETE")
            {
                request.method = request_method::DELETE;
            }

            request.path = path;
            request.version = version;
            if (request.method != request_method::GET)
                http_body = http_lines[http_lines.size() - 1];
            for (int i = 1; i < http_lines.size() - 1; i++)
            {
                if (http_lines[i].empty()) continue;
                std::vector<std::string> line = Utils::Split(http_lines[i], ": ");

                std::string header_name = line[0];
                std::string header_value = line[1];

                if (header_name == "Accepts")
                {

                    if (header_value == "application/json")
                    {
                        request.accepts.push_back(accept_type::APPLICATIONJSON);
                    }
                    else if (header_value == "text/xml")
                    {
                        request.accepts.push_back(accept_type::TEXTXML);
                    }
                    continue;
                }

                if (header_name == "Host")
                {
                    request.host = header_value;
                    continue;
                }

                if (header_name == "User-Agent")
                {
                    request.user_agent = header_value;
                    continue;
                }

                if (header_name == "Connection")
                {
                    if (header_value == "Keep-Alive")
                    {
                        request.connection = connection_state::KEEPALIVE;
                    }
                    else if (header_value == "Close")
                    {
                        request.connection = connection_state::CLOSE;
                    }
                    continue;
                }

                if (header_name == "Content-Length")
                {
                    request.contentLength = atoi(header_value.c_str());
                    continue;
                }

                if (header_name == "Tranfer-Enconding")
                {
                    if (header_value == "chucked")
                    {
                        request.encoding = transfer_encoding::CHUNKED;
                    }
                    else if (header_value == "compress")
                    {
                        request.encoding = transfer_encoding::COMPRESS;
                    }
                    continue;
                }
            }

            if (!http_body.empty()) {
                request.js_body = nlohmann::json::parse(http_body);
            }
            return request;
        }
        auto Parser::PrepareResponse(struct http_response &res) -> std::string
        {
            std::stringstream ss;

            ss << res.version << " ";

            if (res.code == response_code::OK) {
                ss << "200 OK";
            } else if (res.code == response_code::MOVED) {
                ss << "301 Moved Permanently";
            } else if (res.code == response_code::INTERNALERROR) {
                ss << "500 Internal Server Error";
            } else if (res.code == response_code::NOTFOUND) {
                ss << "404 Not Found";
            } else if (res.code == response_code::REDIRECT) {
                ss << "302 Found";
            } else if (res.code == response_code::BADREQUEST) {
                ss << "400 Bad Request";
            }
            ss << res.trailing;

            if (!res.server.empty()) ss << "Server: " << res.server << res.trailing;
            if (!res.location.empty() && res.code == response_code::MOVED) ss << "Location: " << res.location << res.trailing;
            if (res.connection != connection_state::NONE) {
                ss << "Connection: ";
                if (res.connection == connection_state::CLOSE) {
                    ss << "Close";
                } else {
                    ss << "Keep-Alive";
                }
            }
            ss << res.trailing;
            ss << res.trailing << res.body.dump();
            return ss.str();
        }
    }
}
