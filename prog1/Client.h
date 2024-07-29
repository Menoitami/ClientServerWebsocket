#pragma once


#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <string>


namespace beast = boost::beast;       
namespace http = beast::http;         
namespace websocket = beast::websocket; 
namespace net = boost::asio;            
using tcp = boost::asio::ip::tcp;       



class Client{

public:



    Client();
    ~Client();


    void setServerAddress(const std::string& _host, const std::string& _port);
    bool connect();
    bool isConnected();
    bool isServerSet();

    void sendMessage(std::string text);

private:

    std::string host= "";
    std::string port= "";
     bool Connected=false;
    

    net::io_context ioc;
    websocket::stream<tcp::socket> ws{ioc};

};