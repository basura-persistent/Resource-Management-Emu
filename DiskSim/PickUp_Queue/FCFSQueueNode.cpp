

#include "FCFSQueueNode.hpp"

class Request;

FCFSQueueNode::FCFSQueueNode(Request *req) : _request(req), _next(nullptr) {}

FCFSQueueNode *FCFSQueueNode::next() {
    return _next;
}

void FCFSQueueNode::next(FCFSQueueNode *node) {//using this to to insert next available node in the position of the nowdeleted node 
    _next = node;
}

Request *FCFSQueueNode::request() {
    return _request;
}
