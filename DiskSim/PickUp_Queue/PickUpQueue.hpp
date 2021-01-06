#ifndef PICKUP_QUEUE_PICKUP_QUEUE_HPP
#define PICKUP_QUEUE_PICKUP_QUEUE_HPP


#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "FCFSQueueNode.hpp"


class Request;

class PICKUPQueue: public Queue {

public:
    PICKUPQueue(): head(nullptr), tail(nullptr) {}

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~PICKUPQueue();

private:
    FCFSQueueNode *head, *tail;
    FCFSQueueNode *PickUpQueueScanner(FCFSQueueNode  *node);



};

#endif //PICKUP_QUEUE_PICKUP_QUEUE_HPP