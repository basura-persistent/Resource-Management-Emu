


#include "ST_Queue.hpp"
#include "../CommonFiles/Request.hpp"
using namespace std;

void STQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    FCFSQueueNode *rNode = new FCFSQueueNode(request);//creating a new node to store request
    FCFSQueueNode *_head = head;
    int same_trak_count = 0;
    if( empty() ) {
        head = tail = rNode;
    } else {
        tail->next(rNode);
        tail = rNode;

    }
}

int STQueue::same_track_counter(int cRWHeadTrack){
    FCFSQueueNode  *_head = head;
    int same_trak_count = 0;

    if(_head->request()->track() == cRWHeadTrack){
        same_trak_count++;
    }
    while(_head->next() != nullptr){
            if(_head->next()->request()->track() == cRWHeadTrack){
                same_trak_count++;

            }
            _head = _head->next();
        }
        return same_trak_count;
}

Request *STQueue::getRequest() {//extract next request
    if( empty() ) {
        std::cout << "Calling FCFSQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    if(head->request()->track() == 0){
        head=head->next();
        return nullptr;
    }
    if(head == tail){
        Request *last_item = tail->request();
        head = nullptr;
        return last_item;
    }
    FCFSQueueNode *req_holder = nullptr;
    Request *request = nullptr;
    // cout<<"new head"<<endl;
    // head->request()->print();

    req_holder = QueueScanner(head);//scanning for the next item to delete 
    // cout<<"accomplished";
    request = req_holder->request();
    // cout<<"This is the item next";
    // tail->request()->print();
    if(req_holder == head){
        // cout<<"this is the head"<<endl;
        // head->request()->print();
        head = head->next(); 
        // cout<<"head is now ";
        // head->request()->print();
    }
    delete req_holder;
    req_holder = nullptr;

    return request;
}
FCFSQueueNode *STQueue::QueueScanner(FCFSQueueNode  *node){
    // cout<<"gtting to this ";
    FCFSQueueNode *prev = node,*same_track = nullptr, *prevNode2 = nullptr, *node1 = head, *node2 = head->next(), *temp = node, *item2bedeleted= nullptr, *tail_item = nullptr;

    while((temp->next() != nullptr)){
        // if(temp->next()->request()->track() == node->request()->track() &&(temp->next() == tail) ) 
        // tail = temp;
        // temp->request()->print();
        // cout<<"line 72";
        if((temp->next() == tail) && (temp->next()->request()->track() == node->request()->track())){
            // cout<<"found item before tail";
            // temp->request()->print();
            // cout<<"tail";
            // tail->request()->print();
            
            FCFSQueueNode *emptyNode = nullptr;
            tail = temp;
            tail_item = temp->next();
            // tail->next(emptyNode);
            // tail->next(nullptr);
            // cout<<"Deleting this tail node";
            // temp->next()->request()->print();
            // cout<<"new tail";
            // tail->request()->print();
            return tail_item;
        }
        temp = temp->next();

    }

    if ((node->next()->request()->track() == node->request()->track())){
        // cout<<"Line 58"<<endl;

        return head;
    }

    while(prev->next() !=nullptr){
        //sorting to extract any straggelers at the end of the list that may be on same track
        // cout<<"what is next to the head";
        // head->next()->request()->print();
        //if the next item to our current node is equal to
                // cout<<"Line 105"<<endl;

        if(prev->next()->request()->track() == node->request()->track()){//if the item next to the current has a track equal to our requested track delete
            item2bedeleted = prev->next();
            // cout<<"Attching:   "<<endl;
            // prev->request()->print();
            // cout<<"To:    "<<endl;
            // prev->next()->request()->print();
            prev->next(prev->next()->next());           
            return item2bedeleted;       
        }
        prev = prev->next();    
    }
    return head;     
}


bool STQueue::empty() {
    return head == nullptr;
}

void STQueue::print() {
    for(auto cur = head; cur; cur = cur->next() )
        cur->request()->print();
}

STQueue::~STQueue() {
    while( head != nullptr ) {
        FCFSQueueNode *node = head;
        head = node->next();
        delete node;
    }
}