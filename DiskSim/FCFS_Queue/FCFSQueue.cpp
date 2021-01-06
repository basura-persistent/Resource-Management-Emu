/

#include "FCFSQueue.hpp"
#include "../CommonFiles/Request.hpp"

void FCFSQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    FCFSQueueNode *rNode = new FCFSQueueNode(request);//creating a new node to store request
    if( empty() ) {
        head = tail = rNode;
    } else {
        tail->next(rNode);
        tail = rNode;
    }
}

Request *FCFSQueue::getRequest() {//extract next request
    if( empty() ) {
        std::cout << "Calling FCFSQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    FCFSQueueNode *fcfsNode = head;//data structure storing our time/track/sector
    Request *request = fcfsNode->request();//returns request variable data 
    head = head->next();//once we've stored our current request we move the head to the next node 
    if( head == nullptr )//if head is equal to ptr we are at end of request queue
        tail = nullptr;
    delete fcfsNode; //deleting variable that was storing current head
    return request;//returning current request;
}

bool FCFSQueue::empty() {
    return head == nullptr;
}

void FCFSQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

FCFSQueue::~FCFSQueue() {
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
