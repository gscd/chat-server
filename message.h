/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   message.h
 * Author: guy
 *
 * Created on December 10, 2018, 12:07 PM
 */

#ifndef MESSAGE_H
#define MESSAGE_H


class message;
class groupAddRequest; 

class messageBase{
public:
   
    static messageBase* factory(const char* buffer); 
    virtual int getSenderId() const; 
    virtual void setSenderId(int f); 
    char* getBufferPtr(); 
    virtual void setMess(const char* str); 
    virtual ~messageBase(); 

protected:
    messageBase(); 
    messageBase(const char* str, int sender);
    char buffer[1024]; 
    int sender_id; 
};




class message : public messageBase{
public: 

    message(); 
    message(const char* mes, int from, int to); 
     int getSenderId() const; 
    virtual ~message(); 
    void printMesg(); 
    int getDest() const; 
    void setDest(int d); 

private: 
    int dest; 
};



class groupAddRequest:public messageBase
{
public:
     int getSenderId() const; 
    groupAddRequest();
    groupAddRequest(const char* mes, int from, int group, int member); 
    void setMemberId(int i);
    int getMemberId(); 
     int getGroupId(); 
private: 
    int group_id; 
    int member_add_id; 
};

#endif /* MESSAGE_H */

