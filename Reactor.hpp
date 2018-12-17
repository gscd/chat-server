/*---------------------------------------------------------------------------*/
/*  reactor design pattern                                              		     */
/* Author: Guy Fried                                                         */
/* Creation Date: 18.3.18 	                                             */
/*---------------------------------------------------------------------------*/
#ifndef __REACTOR_H__
#define __REACTOR_H__
#include <functional>   // std::function, std::negate
#include <map>
#include<iostream>

template<typename T>
class Reactor
{
public:
    typedef std::function<void(int)> HANDLER;
    explicit Reactor(T& monitor);
    void AddReadHandler(int fd, const HANDLER & handler);
    void EventLoop();
    void DeleteHandler(int fd);

private:

    std::map<int, HANDLER> m_read_handlers;
    T& m_monitor;
};

template<typename T>
Reactor<T>::Reactor(T& monitor): m_monitor(monitor)
{}

template<typename T>
void Reactor<T>::AddReadHandler(int fd, const HANDLER & handler)
{
        m_read_handlers.insert(std::make_pair(fd, handler));
        m_monitor.SetFd(fd);
}

template<typename T>
void Reactor<T>::DeleteHandler(int fd)
{
    m_monitor.FdClear(fd);
    m_read_handlers.erase(fd);
}

template<typename T>
void Reactor<T>::EventLoop()
{
    while (1)
    {
        //start the monitor to listen, after he wake-up, return the number of fd
        int n = m_monitor.Wait();

        for(int i =0; i < n && n != -1 ; i++)
        {
            int fd = m_monitor.NextFd();

            (m_read_handlers[fd])(fd);
        }
    }
}



#endif
