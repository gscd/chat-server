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
    virtual ~messageBase(); 

protected:
    messageBase(); 
};




class message : public messageBase{
public: 

    message(); 
    message(const char* mes, int sender, int dest); 
    ~message();
    void setSenderId(int f); 
    int getSenderId() const; 
    void printMesg(); 
    int getDest() const; 
    void setDest(int d); 
    void setMess(const char* str);
    char* getBufferPtr(); 
    
private: 
    char buffer[1024]; 
    int dest_id; 
    int sender_id; 
};



class groupAddRequest:public messageBase
{
public:
     int getSenderId() const; 
    groupAddRequest();
    groupAddRequest(int src, int group, int member); 
    void setMemberId(int i);
    int getMemberId() const; 
     int getGroupId() const; 
private: 
    int sender_id; 
    int group_id; 
    int member_add_id; 
    
};

#endif /* MESSAGE_H */

