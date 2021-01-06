
#ifndef FCFS_QUEUE_FCFSQUEUENODE_HPP
#define FCFS_QUEUE_FCFSQUEUENODE_HPP


class Request;

class FCFSQueueNode {
public:
    FCFSQueueNode(Request *req);
    FCFSQueueNode *next();
    void next(FCFSQueueNode *node);
    Request *request();

private:
    FCFSQueueNode *_next;
    Request *_request;
};


#endif //FCFS_QUEUE_FCFSQUEUENODE_HPP
