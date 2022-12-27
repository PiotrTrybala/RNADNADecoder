#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "HttpParser.hpp"
#include <vector>
#include "HttpTypes.hpp"
#include <iostream>

namespace decoder {
    namespace http {

        using boost::asio::ip::tcp;
        using registry = std::vector<struct endpoint_reg>;
        using pointer = boost::shared_ptr<TcpConnection>;
        class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
            private:

                void HandleRequest(registry& reg, const boost::system::error_code&);
                void HandleResponse(struct http_response&, const boost::system::error_code&);

                TcpConnection(boost::asio::io_service& ios, registry& reg) : socket(ios), registry(&reg) {}
                tcp::socket socket;
                boost::asio::streambuf request;
                registry* registry;

            public:

                static pointer Create(boost::asio::io_service& ios, decoder::http::registry& reg) {
                    return pointer(new TcpConnection(ios, reg));
                }
                tcp::socket& GetSocket() { return socket; }
                void Start();
        };

    }
}
