
#include "PickUpQueue.hpp"
#include "../CommonFiles/Request.hpp"
using namespace std;

void PICKUPQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    FCFSQueueNode *rNode = new FCFSQueueNode(request);//creating a new node to store request
    if( empty() ) {
        head = tail = rNode;
    } else {
        tail->next(rNode);
        tail = rNode;
    }
}

//GetRequest 
Request *PICKUPQueue::getRequest() {//extract next request
    if( empty() ) {
        std::cout << "Calling FCFSQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    if(head == tail){
        Request *last_item = tail->request();
        head = tail = nullptr;
        return last_item;
    }
    FCFSQueueNode *next_req = head;
    FCFSQueueNode *prev_tail = tail;
    FCFSQueueNode *req_holder = nullptr;
    Request *request = nullptr;
    // cout<<"new hEAD";
    // head->request()->print();
    req_holder = PickUpQueueScanner(next_req);//scanning for the next item to delete 
    //if queue scanner returns an
    request = req_holder->request();
    // cout<<"This is the item next";
    // tail->request()->print();
    if(req_holder == head){
        // cout<<"this is the head"<<endl;
        // head->request()->print();
        head = head->next(); 
    }
    delete req_holder;
    req_holder = nullptr;

    //need to find a way to delete head 
    //then delete any requests found in between. 
    //then delete the next node
    return request;
}

FCFSQueueNode *PICKUPQueue::PickUpQueueScanner(FCFSQueueNode *node){
    // if(tail->next() != nullptr){
    //     FCFSQueueNode *iteration_node = node->next()->next();
    // }
    // cout<<"activating";
    FCFSQueueNode *prev = node,*same_track = nullptr, *next_to_prev = node->next(), *target_node = node->next(), *item2bedeleted= nullptr, *iteration_node = node->next()->next();

    while(iteration_node->next() != nullptr){
        //iterate forward through the list to find any requests at the tail that are greater than then the previous node and less than our node next to previous.
            //return the node if found at the tail 
            if((iteration_node->next() == tail) && (iteration_node->next()->request()->track() >= prev->request()->track()) && (iteration_node->request()->track() <= next_to_prev->request()->track())){
                tail = iteration_node;
                FCFSQueueNode *oldtail = iteration_node->next();
                // cout<<"Found the in between track at tail";
                return oldtail;
            }
            iteration_node = iteration_node->next();   
    }
    //if the tail does not have a track that we can pick up we will revert the iteration node back to the starting position
    target_node = node->next();

    //If we find that the iteration node itself displays a track that we can pick up then we will return that node.
    if((target_node->next()->request()->track() >= prev->request()->track()) && (target_node->next()->request()->track() <= next_to_prev->request()->track())){
        item2bedeleted = target_node->next();
        target_node->next(target_node->next()->next());
        // cout<<"request found here";
        item2bedeleted->request()->print();
        return item2bedeleted;
    }

    iteration_node = node->next()->next();
    //otherwise start iterating through the list to check for any other tracks that meet the condition of being greater than previous node and less than our next node 
    //taking
    while(iteration_node->next() != nullptr){
        if((iteration_node->next()->request()->track() >= prev->request()->track()) && (iteration_node->next()->request()->track() <= next_to_prev->request()->track())){
            // cout<<"activated on node";
            iteration_node->next()->request()->print();
            item2bedeleted = iteration_node->next();
            iteration_node->next(iteration_node->next()->next());
            return item2bedeleted;
        }
        iteration_node = iteration_node->next();
    }

    //otherwise return the item next to the head if no matches are found 
    // cout<<"found no matches";
    head->request()->print();
    return head;
}

bool PICKUPQueue::empty() {
    return head == nullptr;
}

void PICKUPQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

PICKUPQueue::~PICKUPQueue() {
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}