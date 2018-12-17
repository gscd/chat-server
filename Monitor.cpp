#include<iostream>
#include<map>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "Monitor.hpp"



const int PORT =  8888;


Epoll::Epoll():numfds(0), epoll_fd(epoll_create1(0)), events_vec(64)
{
    //init epoll instance
    event.events = EPOLLIN;

}

void Epoll::SetFd(int fd)
{
    struct epoll_event to_add = event;
    to_add.events  = EPOLLIN;
    to_add.data.fd = fd;

    if(-1 == epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &to_add))
    {
        std::cout<<"error ctl " << epoll_fd  << "\n";
    }


    numfds++;
}

void Epoll::FdClear(int fd)
{
	epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);

    numfds--;
}


int Epoll::Wait()
{
    int epoll_ret;

    index_events =0;

    epoll_ret = epoll_wait(epoll_fd, events_vec.data(), 15, -1);

    return epoll_ret;
}

int Epoll::NextFd()
{
    if( 0 != (events_vec[index_events].events & EPOLLIN))
    {
        return events_vec[index_events++].data.fd;
    }
    return -1;
}


/**************************************************************/
/****************************Select****************************/
/**************************************************************/
Select::Select(): max_fd(0), fd_index(0)
{
    FD_ZERO(&master_set);
    FD_ZERO(&working_set);
}

int Select::Wait()
{
    int ret_fd;
    FD_ZERO(&working_set);

    memcpy(&working_set, &master_set, sizeof(master_set));

	fd_index = 0; 
	
    ret_fd = select(max_fd +1, &working_set , NULL , NULL , NULL);
	
    return ret_fd;

}

void Select::SetFd(int fd)
{
    if(fd > max_fd)
        max_fd = fd;

    FD_SET(fd, &master_set);
}

bool Select::FdIsSet(int fd)
{
    return (FD_ISSET(fd,&working_set));
}


void Select::FdClear(int fd)
{
    FD_CLR(fd, &master_set);

}

int Select::NextFd()
{
    for (int fd = fd_index ; fd <= max_fd; fd++)
    {
        if (FD_ISSET(fd, &working_set))
        {
            return fd;

        }
    }

    return -1;
}
