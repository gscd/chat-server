/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include<iostream>
 #include <unistd.h>   
#include<functional>
#include<map>
#include <string>
#include<memory>



#include"group.h"
#include"message.h"
#include"Reactor.hpp"
#include"Monitor.hpp"
#include"TCP_server.h"



TCP::TCP(Reactor<Epoll>& react):
    tcp_socket(socket(AF_INET , SOCK_STREAM , 0)),
    m_react(react),
    group_counter(70)
{   
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port =8888;
    addrlen= sizeof(address);
    bind(tcp_socket, reinterpret_cast<struct sockaddr *>(&address), sizeof(address));
    listen(tcp_socket, 3);
    std::cout << "listen on port " <<address.sin_port << std::endl; 
}

void TCP::Accept()
{
    int new_socket = accept(tcp_socket,
                    reinterpret_cast<struct sockaddr *>(&address),
                    reinterpret_cast<socklen_t*>(&addrlen));
   
    char buffer[1024]; 
    message m;
    read( new_socket , &m, sizeof(message));
    
    int sender_id = m.getSenderId(); 
  
    std::shared_ptr<client> new_client(new user(sender_id,new_socket)); 
    
    client_map[sender_id] = new_client;
    
    std::cout << "sender_id" << sender_id << std::endl;  
    std::cout<<" insert into map: " << client_map[m.getSenderId()] ->getId() << " sk: "<<  client_map[m.getSenderId()] ->getSk() <<std::endl; 
   
    m_react.AddReadHandler(new_socket, std::bind(&TCP::Read, this,std::placeholders:: _1));
}


void TCP::CreateGroup(message& m)
{
   
    std::shared_ptr<client> new_group(new group(group_counter,0)); 
    
    std::cout<<"Create group\n"; 
    
    client_map[group_counter] = new_group;
    
    std::cout<<" insert group into map: " << client_map[group_counter]->getId() << " sk: "<<  client_map[group_counter] ->getSk() <<std::endl; 
   std::dynamic_pointer_cast<group>(new_group)->addMember(client_map[m.getSenderId()]);
      
    
    std::cout<<" sending " <<std::endl; 
    
    message send_m(std::to_string(group_counter).c_str(), 0, m.getSenderId()); 
    send(client_map[m.getSenderId()]->getSk(), &send_m, sizeof(message), 0);

    group_counter++;
}


void TCP::AddMemberGroup(groupAddRequest & m)
{
     int member_to_add = m.getMemberId();
     int group_id = m.getGroupId(); 
     
     std::cout<<" add member " <<member_to_add;
     std::cout<<" group_id" <<group_id << std::endl;
     std::shared_ptr<group> group_ptr = std::dynamic_pointer_cast<group>(client_map[group_id]);
     
    group_ptr->addMember(client_map[member_to_add]);
}


void TCP::Read(int fd){

    char buffer[1024];  //data buffer of 1K
    char mes[1024];
    memset(buffer, '\0', 1024); 
   
    
    if ((read( fd , buffer, sizeof(buffer))) <= 0)
    {
       //Somebody disconnected , get his details and print
       getpeername(fd , reinterpret_cast<struct sockaddr*>(&address) , \
                            reinterpret_cast<socklen_t*>(&addrlen));
       printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
       
       for(auto& e : client_map)
       {
           if((e.second)->getSk() == fd)
           {
               std::cout<<"user "<< e.first << " disconnect\n"; 
               client_map.erase(e.first); 
               
           }
       }
       
       //client_map.erase()
       m_react.DeleteHandler(fd);
       close(fd);
    }
    
    else if(!strcmp("group",buffer))
    {
        read(fd , buffer, sizeof(buffer));
        
        if(!strcmp("create",buffer))
        {
            message m; 
            read( fd , &m, sizeof(message));
            std::cout << "user type group create\n"; 
            CreateGroup(m);

        }
        else if(!strcmp("add member",buffer))
        {
            groupAddRequest ar;
            read(fd, &ar, sizeof(groupAddRequest)); 
            
            std::cout << "user type add member\n"; 
            AddMemberGroup(ar);
        }  
    }
    else
    {
        message m; 
        read( fd , &m, sizeof(message));
      
        int x = m.getSenderId(); 
     
        std::cout<<x<< std::endl; 
        
        int sid = m.getDest(); 
        
        client_map[sid]->sendMess(m);
  
    }
}



void TCP::ReadGroup(int id)
{

}


int TCP::getSocket()
{
    return tcp_socket;
}
