#include "Client.h"


Client::Client(){};

Client::~Client(){};


void Client::setServerAddress( const std::string& _host, const std::string& _port){

    host = _host;
    port=_port;

}


bool Client::connect(){

    if (host.empty()){

        std::cerr<<"address not set\n";
        return false;
    }

    try
    {

        tcp::resolver resolver{ioc};
       
        
        auto const results = resolver.resolve(host, port);

        auto ep = net::connect(ws.next_layer(), results);

        ws.handshake(host+':' + std::to_string(ep.port()), "/");

        beast::flat_buffer buffer;

        Connected=true;
    }
    catch(std::exception const& e)
    {
        std::cerr << "I m not connected to server\n";
        return false;
    }
    return true;



}

void Client::sendMessage(std::string text) {
    try {
        
        ws.write(net::buffer(text));

    }
    catch (std::exception const& e) {
        Connected = false;
        connect();
        if (Connected){
            ws.write(net::buffer(text));
        }
    }
}



bool Client::isConnected(){
        return Connected;
    }


bool Client::isServerSet(){
        if (host.empty()){

            return false;
        }
        else return true;
     }