#include <iostream>
#include "engine/DecoderEngine.hpp"
#include "engine/EngineTypes.hpp"
#include "api/include/HttpParser.hpp"
#include "api/include/HttpUtils.hpp"
#include "api/include/HttpServer.hpp"
#include "api/include/HttpTypes.hpp"
#include <asio.hpp>

using namespace decoder::engine;
using namespace decoder::http;

struct http_response PostIndex(struct http_response& res, struct http_request& req) {
    res.code = ResponseCode::OK;
    res.server = "My_Server:)";
    res.connection = ConnectionState::KEEPALIVE;
    res.body = R"(
        "response": "I am feeling good today. It's snowing outside.
    )";
    return res;
}

auto main() -> int {
    // auto* engine = new DecoderEngine();
    // struct DecoderInput input = {
    //     .input = "AAAUGAACGAAAAUCUGUUCGCUUCAUUCAUUGCCCCCACAAUCCUAGGCCUACCC"
    // };
    // std::vector<struct DecoderResult> results = engine->GetResults(input);
    // // for (int i = 0; i < 3; i++) {
    // //     std::cout << "#" << (i + 1) << ": " << results[i].result << "\n";
    // // }
    // delete engine;


    // HttpServer server(8080);

    // server.post("/decode", DecodeRoute());
    // server.default(DefaultRoute());

    // server.run();

    // std::string get_http_request =
    // "GET / HTTP/1.1\r\n"
    // "Host: example.com\r\n"
    // "Connection: keep-alive\r\n"
    // "Keep-Alive: 300\r\n"
    // "Accept: application/json\r\n"
    // "\r\n";
    // struct http_request req = Parser::ParseRequest(get_http_request);

    // std::cout << req.host << std::endl;
    // std::cout << req.path << std::endl;

    // std::string post_http_request =
    // "POST /decode HTTP/1.1\r\n"
    // "Host: example.com\r\n"
    // "Connection: keep-alive\r\n"
    // "Keep-Alive: 300\r\n"
    // "Accept: application/json\r\n"
    // "\r\n"
    // "{\"name\": \"piotrek\"}";

    // struct http_request req1 = Parser::ParseRequest(post_http_request);

    // struct http_response res;

    // res.code = ResponseCode::OK;
    // res.server = "Hello-Server";
    // res.cache.push_back(CacheControls::MINFRESH);
    // res.connection = ConnectionState::CLOSE;
    // res.body = {
    //     {"name", "bartek"}
    // };

    // std::string prepared = Parser::PrepareResponse(res);

    // std::cout << prepared << std::endl;

    boost::asio::io_context ctx;

    HttpServer server {ctx, 3000};

    server.get("/", PostIndex);

    ctx.run();


    return 0;
}
