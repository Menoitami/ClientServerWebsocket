#include "StringProcessor.h"


 StringProcessor::StringProcessor(){};

 StringProcessor::StringProcessor(Client* _client){

    this->client = _client;
    if (!client->isServerSet()) throw std::logic_error("Server is t set");
    client->connect();


 };


 
 StringProcessor::~StringProcessor(){

    delete client;

 };

void StringProcessor::process(){
    std::string message;
    std::unique_lock<std::mutex> lock(transferlock, std::defer_lock);


    while (true){

      size_t i=0;  

        std::cout<<"Write your message: ";
        std::cin>>message;
    

        if (message.length()>64){
            std::cout<<"message is too long\n";
            continue;
        }

        std::sort(message.begin(), message.end(), std::greater<char>());
        if (!(is_digit(message.front()) && is_digit(message.back()))){

            std::cout<<"the message contains non-numeric characters\n";
            continue;

        }
      

        
        while (i < message.length()) {
            if ((message[i] % 2) == 0) {
                
                message.erase(i,1);
                message.insert(i, "KB");
                
                
                ++i; 
            }
            
            ++i;
        }


        

        setBuffer(message);
        cv.wait(lock);
        
    }
}




void StringProcessor::transfer(){
    std::unique_lock<std::mutex> lock(transferlock);
    std::string message;
    int sum;

    while(true){
    
        cv.wait(lock);

        message= getAndClearBuffer();
        sum=0;

        for (char c : message) sum += is_digit(c) ? static_cast<int>(c)-48 : 0; 
    
        
        std::cout<<"Message: "<<message<<"\nSum:"<<sum<<"\n";

        client->sendMessage(std::to_string(sum));

        cv.notify_one();
    }
}



void StringProcessor::setBuffer(std::string str){

    std::lock_guard<std::mutex> guard(bufferAccess);

    buffer = str;

    cv.notify_one();

}


std::string StringProcessor::getAndClearBuffer(){

    std::lock_guard<std::mutex> guard(bufferAccess);
    auto i = buffer;
    buffer.clear();
    return i;

}


  bool StringProcessor::is_digit(char c) {
    return c >= '0' && c <= '9';}