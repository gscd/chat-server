/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"message.h"
#include<string.h>
#include<iostream>

messageBase::messageBase(const char* str, int sender)
{
    memcpy(buffer , str, 1024);
    sender_id = sender;
}
messageBase::messageBase()
{}

messageBase* messageBase::factory(const char* buffer)
{
    if(!strncmp("private", buffer,7))
    {
        return new message; 
    }
    else if(strncmp("group add", buffer,7))
    {
        return new groupAddRequest; 
    }
}

void messageBase::setMess(const char* str)
{
    memset(buffer, '\0', 1024); 
    memcpy(buffer, str, strlen(str)); 
}

int messageBase::getSenderId() const
{
    return sender_id; 
}

void messageBase::setSenderId(int f)
{
    sender_id = f; 
}

char* messageBase::getBufferPtr()
{
    return buffer; 
 }
 
messageBase::~messageBase()
{}


//int message::getSenderId() const
//{
//    return getSenderId();
//}


message::message(const char* mes, int from, int to):
messageBase(mes, from), dest(to)
{}

message::message()
{}

message::~message()
{}

void message::setDest(int d)
{
    dest = d; 
}

int message::getSenderId() const
{
    return getSenderId(); 
}

int message::getDest() const 
{
    return dest; 
}


 
groupAddRequest::groupAddRequest(const char* mes, int from, int group, int member):
messageBase(mes,from),group_id(group), member_add_id(member)
{}

 void groupAddRequest::setMemberId(int i)
 {
     member_add_id = i; 
 }
 
 int groupAddRequest::getMemberId()
 {
     return member_add_id; 
 }
 groupAddRequest::groupAddRequest()
 {}
 
 int  groupAddRequest::getSenderId() const
 {
    return getSenderId(); 
}
 
int groupAddRequest::getGroupId() 
{
    return group_id; 
}