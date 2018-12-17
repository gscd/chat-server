/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   group.h
 * Author: guy
 *
 * Created on December 10, 2018, 4:54 PM
 */

#ifndef GROUP_H
#define GROUP_H
#include<vector>
#include<memory>
#include"message.h"


class client{
public: 
    client(int i, int sk); 
    virtual ~client(); 
    virtual void sendMess(message& m); 
    int getId(); 
    int getSk();
private:
    int sk; 
    int id;
};


class group:public client{
public:
    group(int i, int sk);
    ~group(); 
    virtual void addMember(std::shared_ptr<client> c); 
    void removeMember(std::shared_ptr<client> c); 
    void sendMess(message& m); 
    
private:
    
    std::vector<std::shared_ptr<client>> members; 
};


class user: public client{
public:
    user(int i, int sk); 
    ~user(); 
    void sendMess(message& m);
    
private: 
   
};


#endif /* GROUP_H */

