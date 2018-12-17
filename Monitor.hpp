/*---------------------------------------------------------------------------*/
/*  Monitor                                              		     */
/* Author: Guy Fried                                                         */
/* Creation Date: 18.3.18 	                                             */
/*---------------------------------------------------------------------------*/
#ifndef __MONITOR_H__
#define __MONITOR_H__
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<vector>
#include <sys/epoll.h>

class Select
{
public:
    explicit Select();
    /*genrated dtor*/
    int Wait();
    bool FdIsSet(int fd);
    void SetFd(int fd);
    void FdClear(int fd);
    int NextFd();

private:
    int max_fd;
    int fd_index;
    fd_set master_set;
    fd_set working_set;

};


class Epoll
{
public:
    explicit Epoll();
    /*genrated dtor*/
    int Wait();
    bool FdIsSet(int fd);
    void SetFd(int fd);
    void FdClear(int fd);
    int NextFd();

private:
    int numfds;
    int epoll_fd;
    std::vector<epoll_event> events_vec;
    epoll_event event;
    int index_events;

};

#endif
