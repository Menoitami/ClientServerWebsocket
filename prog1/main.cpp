#include <iostream>
#include <thread>
#include <string>
#include "StringProcessor.h"
#include <boost/filesystem.hpp>
#include "Client.h"


int main(){

    Client* client= new Client();
    client->setServerAddress("127.0.0.1", "8083");
    StringProcessor prog1(client);

    std::thread th1(&StringProcessor::process, &prog1);
    std::thread th2(&StringProcessor::transfer, &prog1);
   
    th2.join();
    th1.join();
   
    return 0;
}