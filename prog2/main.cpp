#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <string>
#include <thread>
#include "Server.h"

//------------------------------------------------------------------------------

int main(int argc, char* argv[])
{

       std::thread th1([](){
              Server server;
              server.startServer();
       });

       th1.join();

}