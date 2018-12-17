/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include"message.h"
#include<string.h>
#include<iostream>


messageBase::messageBase()
{}
messageBase::~messageBase()
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




message::message(const char* mes, int sender, int dest)
{
    memcpy(buffer , mes, 1024);
    sender_id = sender;
    dest_id = dest; 
}

message::message()
{}

message::~message()
{}

void message::setDest(int d)
{
    dest_id = d; 
}

int message::getSenderId() const
{
    return sender_id; 
}

int message::getDest() const 
{
    return dest_id; 
}

void message::setMess(const char* str)
{
    memset(buffer, '\0', 1024); 
    memcpy(buffer, str, strlen(str)); 
}
 
void message::setSenderId(int f)
{
    sender_id = f; 
}

char* message::getBufferPtr()
{
    return buffer; 
 }
 

groupAddRequest::groupAddRequest(int src, int group, int member): 
sender_id(src), group_id(group), member_add_id(member)
{}

 groupAddRequest::groupAddRequest()
 {}

 void groupAddRequest::setMemberId(int i)
 {
     member_add_id = i; 
 }
 
 int groupAddRequest::getMemberId() const
 {
     return member_add_id; 
 }

 
 int  groupAddRequest::getSenderId() const
 {
    return sender_id; 
}
 
int groupAddRequest::getGroupId() const
{
    return group_id; 
}