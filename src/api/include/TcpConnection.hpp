#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "HttpParser.hpp"

namespace decoder {
    namespace http {
        using boost::asio::ip::tcp;
        class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {



            private:

                void handle_request(const boost::system::error_code&);
                void handle_response(const boost::system::error_code&);

                TcpConnection(boost::asio::io_service& ios) : socket_(ios) {}

                tcp::socket socket_;

                std::string request;


            public:
                typedef boost::shared_ptr<TcpConnection> pointer;
                static pointer create(boost::asio::io_service& ios) {
                    return pointer(new TcpConnection(ios));
                }
                tcp::socket& socket() { return socket_; }
                void start();
        };

    }
}
