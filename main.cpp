/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: guy
 *
 * Created on December 10, 2018, 12:02 PM
 */

#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include<iostream>
#include<map> 
#include"message.h"
#include"Monitor.hpp"
#include"Reactor.hpp"
#include"TCP_server.h"



using namespace std;

/*
 * 
 */

//tatic const int PORT = 7890; 


int main(int argc, char** argv) {

    int sockfd, new_sockfd; // Listen on sock_fd, new connection on new_fd
    struct sockaddr_in host_addr, client_addr;// My address information
    socklen_t sin_size;
    int recv_length=1, yes=1;
    char buffer[1024];
    
    Epoll e; 
    Reactor<Epoll> react(e);
     TCP tcp(react);

    react.AddReadHandler(tcp.getSocket(), std::bind(&TCP::Accept, &tcp));


    react.EventLoop();



    return 0;
}

