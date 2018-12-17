#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include<iostream>
 #include <unistd.h>
#include <thread>         // std::thread
#include<mutex>
#include<string>
#include<sstream>
#include <errno.h>
#include <fstream>


#include "/home/guy/NetBeansProjects/chat/message.h"


static const int PORT = 8888; 
static int my_id; 
static std::mutex lock; 
int sock = 0; 


//void createGroupRequest(message& m)
//{
//        m.setDest(0); 
//        m.setFrom(my_id); 
//        
//        send(sock , &m , sizeof(message) , 0 ); 
//     
//        //read( sock , &m, sizeof(message)); 
//        std::cout << "send group create request\n";   
//}
//
//void GroupAddRequest(std::string s)
//{
//        int memberToAdd; 
//        int groupDest; 
//        std::string str; 
//        
//        lock.unlock();
//        std::cout << "Enter group destination: \n";
//        lock.unlock();
//
//        getline (std::cin,str);
//        std::stringstream(str) >> groupDest;
//      
//        lock.unlock();
//        std::cout << "Enter member ID  to add: \n";
//        lock.unlock();
//
//        getline (std::cin,str);
//        std::stringstream(str) >> memberToAdd;
//      
//        
//        groupAddRequest group_m(s.c_str(),my_id,groupDest,memberToAdd);
//        std::cout<< "member id" <<group_m.getMemberId() <<"\n"; 
//        send(sock , &group_m , sizeof(groupAddRequest) , 0 ); 
//     
//     
//}


static void read_m()
{
     message m; 
     
       while(1)
    {
        read( sock , &m, sizeof(message)); 
        lock.lock();
        printf("\n%d write: %s \n", m.sender_id, m.getBufferPtr());
        lock.unlock();
       }
}

static void write_m()
{
        int dest; 
        size_t len; 
        std::string str; 
        std::string str2; 
        std::string dest_str; 
        
       
            
        
        while(1)
        {
            lock.lock();
            printf("what you want to do\n");
            lock.unlock();
            getline (std::cin, str);
           
            if(str == "private")
            {
             
      
                lock.lock();
                std::cout << "Enter message: \n";
                lock.unlock();
                
                getline (std::cin, str2);
                //m.setMess(str2.c_str()); 
                
                lock.lock();
                std::cout << "Enter destination: \n";
                lock.unlock();

                getline (std::cin,dest_str);
                std::stringstream(dest_str) >> dest;

                message m(str2.c_str(), my_id ,dest);

               // std::cout << "going to send: " << m.getSenderId()<<"\n";
               //  std::cout <<  m.getBufferPtr()<<"\n";
                
                send(sock ,str.c_str(), 1024 , 0 ); 
                send(sock , &m , sizeof(message) , 0 ); 
                
                
            }
            else if(str == "group create")
            {
                //m.setMess(str.c_str()); 
               // createGroupRequest(m); 
                
            }
            else if(str== "group add")
            {
                //GroupAddRequest(str); 
                
            }
//            else{
//                m.setMess(str.c_str()); 
//                lock.unlock();
//                std::cout << "Enter destination: \n";
//                lock.unlock();
//
//                getline (std::cin,str);
//                std::stringstream(str) >> dest;
//                m.setDest(dest); 
//                m.setFrom(my_id); 
//                send(sock , &m , sizeof(message) , 0 ); 
//            }
        }
}



int main(int argc, char** argv)
{
    struct sockaddr_in address; 
    struct sockaddr_in serv_addr; 
    
   
     
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = PORT; 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed- %s \n",strerror(errno)); 
        return -1; 
    } 
    
    my_id =  atoi(argv[1]); 
    
    
    
     message first("new" ,my_id,1); 
     send(sock , &first , sizeof(message) , 0 );
    
    
     
    std::thread read (read_m);   
    std::thread write (write_m);
    
    read.join(); 
    write.join();
    
    return 0; 
}
