#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <string>
#include <thread>


namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


class Server{

public:


    Server();
    ~Server();

    void setAddress(const std::string& ip, const unsigned short int& port);
    void startServer();


private:

    net::ip::address address;
    unsigned short port=0;

    void getString();

    void connect();

    void processValue(const std::string& message);


    






};