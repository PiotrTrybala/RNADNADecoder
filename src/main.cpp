#include <iostream>
#include <asio.hpp>

#include "engine/DecoderEngine.hpp"
#include "engine/EngineTypes.hpp"
#include "api/include/HttpParser.hpp"
#include "api/include/HttpUtils.hpp"
#include "api/include/HttpServer.hpp"
#include "api/include/HttpTypes.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace decoder::engine;
using namespace decoder::http;

struct http_response PostEngineDecodeRNA(struct http_response& res, struct http_request& req) {
    auto* engine = new DecoderEngine();
    std::string input = req.js_body["input"].get<std::string>();
    if (input.empty()) {
        res.code = response_code::BADREQUEST;
        res.body = R"({"response": "provided input was empty"})";
        return res;
    }
    std::vector<std::string> results = engine->GetResults(input);
    res.code = response_code::OK;
    res.server = "RNADecoderEngine";
    res.connection = connection_state::CLOSE;
    res.corsMode = cors::ALL;
    json res_body = {
        {"output0", results[0]},
        {"output1", results[1]},
        {"output2", results[2]}
    };
    res.body = res_body;
    return res;
}

auto main() -> int {

    auto console = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");

    boost::asio::io_context server_ctx;
    HttpServer server {server_ctx, 3000};
    server.Post("/decode", PostEngineDecodeRNA);
    server_ctx.run();
    return 0;
}
