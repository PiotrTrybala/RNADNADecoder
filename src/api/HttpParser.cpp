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

            std::vector<std::string> http_lines = Utils::split(req, crlf);

            std::vector<std::string> method_header = Utils::split(http_lines[0], " ");

            std::string method = method_header[0];
            std::string path = method_header[1];
            std::string version = method_header[2]; // :)
            if (method == "GET")
            {
                request.method = RequestMethod::GET;
            }
            else if (method == "POST")
            {
                request.method = RequestMethod::POST;
            }
            else if (method == "PUT")
            {
                request.method = RequestMethod::PUT;
            }
            else if (method == "DELETE")
            {
                request.method = RequestMethod::DELETE;
            }

            request.path = path;
            request.version = version;
            if (request.method != RequestMethod::GET)
                http_body = http_lines[http_lines.size() - 1];
            for (int i = 1; i < http_lines.size() - 1; i++)
            {
                if (http_lines[i].empty()) continue;
                std::vector<std::string> line = Utils::split(http_lines[i], ": ");

                std::string header_name = line[0];
                std::string header_value = line[1];

                std::cout << header_name << " | " << header_value << std::endl;

                if (header_name == "Accepts")
                {

                    if (header_value == "application/json")
                    {
                        request.accepts.push_back(AcceptTypes::APPLICATIONJSON);
                    }
                    else if (header_value == "text/xml")
                    {
                        request.accepts.push_back(AcceptTypes::TEXTXML);
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
                        request.connection = ConnectionState::KEEPALIVE;
                    }
                    else if (header_value == "Close")
                    {
                        request.connection = ConnectionState::CLOSE;
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
                        request.encoding = TransferEncodings::CHUNKED;
                    }
                    else if (header_value == "compress")
                    {
                        request.encoding = TransferEncodings::COMPRESS;
                    }
                    continue;
                }
            }
            if (!http_body.empty()) {
                request.js_body = nlohmann::json::parse(http_body);
            }
            return request;
        } auto Parser::PrepareResponse(struct http_response &res) -> std::string &
        {
            std::string response;
            return response;
        }
    }
}
