group/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   group.cpp
 * Author: guy
 * 
 * Created on December 10, 2018, 4:54 PM
 */
#include <sys/types.h>
#include <sys/socket.h>
#include<iostream>

#include "group.h"


/*-------------client----------------*/
 client::client(int i, int sk):id(i), sk(sk)
 {}
 
 client::~client()
 {}
 
 int client::getId()
 {
     return id; 
 } 
 
 int client::getSk()
 {
     return sk; 
 }
 
void client::sendMess(message& m)
{}

/*-----------group----------------*/
group::group(int i, int sk):client(i, sk){

}

group::~group() {

}
void group::addMember(std::shared_ptr<client> c)
{
    members.push_back(c); 
    
}
void group::removeMember(std::shared_ptr<client> c)
{

}

void group::sendMess(message& m)
{
    for(auto& c : members)
    {
        c->sendMess(m); 
    }
}

/*--------------user---------------*/



user::user(int id, int sk):client(id,sk)
{}

user::~user()
{}

void user::sendMess(message& m)
{
    std::cout<<"User sendMess from: "<<m.getSenderId()<< " to sk" << getSk() << std::endl; 
    int sk = getSk(); 
    send(sk, &m, sizeof(message),0); 
}


