
#ifndef ST_QUEUE_ST_QUEUE_HPP
#define ST_QUEUE_ST_QUEUE_HPP


#include<iostream>
#include "../CommonFiles/Queue.hpp"
#include "FCFSQueueNode.hpp"

class Request;

class STQueue: public Queue {

public:
    STQueue(): head(nullptr), tail(nullptr), trail_var(nullptr) {}

    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    int same_track_counter(int cRWHeadTrack);

    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~STQueue();


private:
    FCFSQueueNode *head, *tail, *trackqueue, *trail_var;
    FCFSQueueNode *QueueScanner(FCFSQueueNode  *node);
};


#endif //FCFS_QUEUE_FCFSQUEUE_HPP
