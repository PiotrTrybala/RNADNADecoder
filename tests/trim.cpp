#define DOCTEST_CONFIG_IMPLEMENTED_WITH_MAIN
#include "HttpUtils.hpp"
#include "./../lib/doctest/doctest/doctest.h"

using decoder::http::Utils;

TEST_CASE("trim test") {

    std::string a1 = Utils::trim("a a a a");
    std::string a2 = Utils::trim("bb bb bb bb");
    std::string a3 = Utils::trim("c  c  c  c");
    std::string a4 = Utils::trim("d| d|   |d   |d");
    std::string a5 = Utils::trim("Piotrek is good");
    std::string a6 = Utils::trim("akld adkj dfsjlk fdlj");
    std::string a7 = Utils::trim("klfj aaa 111 111");
    std::string a8 = Utils::trim("klfj aaa 111 111  11          111");

    CHECK(a1 == "aaaa");
    CHECK(a2 == "bbbbbbbb");
    CHECK(a3 == "cccc");
    CHECK(a4 == "d|d||d|d");
    CHECK(a5 == "Piotrek is good");
    CHECK(a6 == "akldadkjdfsjlkfdlj");
    CHECK(a7 == "klfjaaa111111");
    CHECK(a8 == "klfjaaa11111111111");
}
