#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "HttpParser.hpp"
#include <vector>
#include "HttpTypes.hpp"

namespace decoder {
    namespace http {
        using boost::asio::ip::tcp;
        using v_reg = std::vector<struct endpoint_reg>;
        class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
            private:

                void handle_request(const boost::system::error_code&);
                void handle_response(const boost::system::error_code&);

                TcpConnection(boost::asio::io_service& ios, v_reg& reg) : socket_(ios), registry(reg) {}

                tcp::socket socket_;

                boost::asio::streambuf request;

                v_reg registry;

            public:
                typedef boost::shared_ptr<TcpConnection> pointer;
                static pointer create(boost::asio::io_service& ios, v_reg& reg) {
                    return pointer(new TcpConnection(ios, reg));
                }
                tcp::socket& socket() { return socket_; }
                void start();
        };

    }
}
