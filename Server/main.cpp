#include <iostream>
#include "zmq.hpp"
#include <cassert>
int main()
{
   std::cout << "hi" << std::endl;
   //Say hi
   zmq::context_t context (1);
   zmq::socket_t socket (context, ZMQ_REP);
   socket.bind ("tcp://eth0:5867");
   
   while(true)
   {
      zmq::message_t message;
      socket.recv (&message);
      std::string messageString = std::string(static_cast<char*>(message.data())) + '\0';
      std::cout << "received data!"<<std::endl;
      std::cout << messageString << std::endl;
      
      std::string rest = messageString;
      std::string data[5];
      for(int i = 0; i < 5; i++)
      {
         size_t delimLocation = rest.find('*');
         if(delimLocation == std::string::npos) //no delim found
         {
            //throw error
         }
         else
         {
            data[i] = rest.substr(0, delimLocation); //sets data[i] from begin
                                                     // to next '*' character
            rest = rest.substr(delimLocation+1); //sets rest to everything after
                                               //the first '*'
            std::cout << "Part " << i << ": "<<data[i] << std::endl;
         }
      }
      //double lati, longi;
      //std::string route;
     //long upTime;
      //char direction;
      
      //data[0] >> lati;
      //data[1] >> longi;
      //route = data[2];
      //data[3] >> upTime;
      //data[4] >> direction;
      
      //someHandlerFunction(lati, longi, route, upTime, direction); //should thread and free this to make connections
      
      zmq::message_t reply (50);
      memcpy ((void *) reply.data (), "HWORLD DUDE", 40);
      std::cout << "Sending REPLY" << std::endl;
      socket.send (reply);
      //Wait for new connection
      //spin new connection in its own thread
   }
   return 0;
}