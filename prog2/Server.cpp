#include "Server.h"





Server::Server(){

    this->address = net::ip::make_address("127.0.0.1");
    this->port = 8083;

};


Server::~Server(){};



void Server::processValue(const std::string& message){

    int number= std::stoi(message);

    if (number>99  && number%32==0){

        std::cout<<"Message has been received\nMessage: "<<number<<"\n";

    }
    else
        std::cout<<"Error: Received an incorrect message\n";



}




void Server::setAddress(const std::string& address, const unsigned short int& port){

    this->address = net::ip::make_address(address);
    this->port = port;


}



void Server::startServer(){


    if(port == 0){
        std::cerr<<"Error: something wrong with address";
    }
    net::io_context ioc{1};

        tcp::acceptor acceptor{ioc, {address, port}};
        std::cout<<"Server is running\n";

        for(;;)
        {

            tcp::socket socket{ioc};

            acceptor.accept(socket);

            std::cout<<"Client Connected"<<"\n";
            
            std::thread{ [q{std::move(socket)}, this]() mutable { 
                        
                websocket::stream<tcp::socket> ws{std::move(const_cast<tcp::socket&>(q))};
                    
                        
                        ws.accept();
                        std::string sendString;


                        while(true)
                        {
                            try
                            {
                                        
                            beast::flat_buffer buffer;
                            ws.read(buffer);

                            std::string message = beast::buffers_to_string(buffer.cdata());
                            processValue(message);

                            }
                            catch(beast::system_error const& se)
                            {
                                if(se.code() != websocket::error::closed)
                                {
                                    std::cout << se.code().message() << std::endl;
                                    break;
                                }
                            }
                        }
                }
            }.detach();
        }






}