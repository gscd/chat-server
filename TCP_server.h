#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<map>
#include<vector>
#include<memory>

#include"Reactor.hpp"
#include"Monitor.hpp"
#include"message.h"
#include"group.h"


class TCP
{
public:
    explicit TCP(Reactor<Epoll>& react);
    void Accept();
    void CreateGroup(messageBase& m); 
    void AddMemberGroup(groupAddRequest& m); 
    void Read(int fd);
    void ReadGroup(int id);
    int getSocket();
    void handleGroup(int id); 
private:
    int addrlen;
    struct sockaddr_in address;
    int tcp_socket;
    Reactor<Epoll>& m_react;
    
    std::map<int, std::shared_ptr<client>> client_map; 

    
    int group_counter; 
};