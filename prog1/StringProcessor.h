#pragma once 
#include <iostream>
#include <thread>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include "Client.h"


class StringProcessor{

public:

    StringProcessor(Client* client);
    ~StringProcessor();

    void process();
    void transfer();


private:

    StringProcessor();

    
    Client* client;
    
    bool is_digit(char c);

    void setBuffer(std::string str);
    std::string getAndClearBuffer();

    

    
    std::string buffer;
    std::mutex bufferAccess;
    std::mutex transferlock;
    std::condition_variable cv;


};
