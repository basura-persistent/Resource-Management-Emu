
#include <iostream>
#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <unistd.h>
#include "../CommonFiles/Request.hpp"
#include "ST_Queue.hpp"

using namespace std;

STQueue *createSTQueueFromInputFile( int argc, char *argv[] ) {//this will return a queue nodes

    if( argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }
    
    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable top open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(1);
    }

    auto *queue = new STQueue();//calling pointer object to FCFS queue so we can run all functions from STQueue class

    int time, track, sector;
    int numRequestsGenerated_input = 0;
    int numRequestsInQueue_input = 0;
    Request *request_input = nullptr;
    double previousTimeStamp_input = 0.0;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);//using Request data structure to store time tracks and sectors
        queue->addRequest(request, 0, 0);
        numRequestsGenerated_input++;
        numRequestsInQueue_input++;
    }
    // queue->print();

    while(numRequestsInQueue_input > 0){
        request_input = queue->getRequest();//return the next item we should delete 
        cout << "Deleting the following request";
        // cout<<"struggling here";
        request_input->print();
        delete request_input;
        request_input = nullptr;
        numRequestsInQueue_input--;
    }
    cout<<"All Requests Serviced";
    return queue;
}

Request *generateRandomRequest() {
    // Randomly generates and returns a request. The time of each
    // subsequent request is larger than that of the previous one.

    static int currentTime = 0;

    enum {
        MAX_TIME_INTERVAL = 100,
        MAX_TRACK = 10,
        MAX_SECTOR = 30
    };

    currentTime += (int) (random() % MAX_TIME_INTERVAL + 1);// advance current time by at most 100 msecs
    int sector = (int) (random() % MAX_SECTOR);
    int track = 0;
    int i = 0;
    while(i < 10){
        int possible_track = random() % MAX_TRACK;
        if(possible_track > 0){
            int track = possible_track;
            return new Request(currentTime, track, sector);
        }
        i++;
    }
    // int track = (int) (random() % MAX_TRACK);

    return nullptr;
}

enum Actions {
    ADD_A_REQUEST = 0,
    GET_A_REQUEST = 7,
    INSPECT_QUEUE = 9,
};

const int ACTION_RANGE = 10;



STQueue *createSTQueueFromRandomValues(int numRequestsToGenerate, int numTestsToRun) {
    // This function runs numTestsToRun to test the FCFS queue. Each test consists of one
    // of the following operations:
    //
    //   1. adding a random request to the queue.
    //   2. removing (and deleting) a request from the queue.
    //   3. determining if the queue is empty or not.

    // numRequestsToGenerate provides a limit on the number of requests to be generated.
    // You can force the queue to become empty by setting the value of numTestsToRun
    // far greater than numRequestsToGenerate. Setting numRequestsToGenerate greater
    // than numTestsToRun will keep many requests in the queue.

    // Once all tests are run, the queue gets emptied, if it is not already empty.

    // FCFS is a simple queue and as a result, testing whether it organizes the requests
    // correctly or not is simple. To that end, we keep track of the timestamp of
    // the last request that we remove from the queue. Every time that we remove
    // a request from the queue, we expect its timestamp to be larger than that of
    // the previous one. If that relationship doesn't hold, we print an error message.

    // We use enum Action to give weight to each of the three operations that
    // we perform to test the queue. To perform a test, we draw a random number between
    // 0 and 9 and depending on how its value relates to the range of values that enum
    // Action provides and run a test accordingly.
    //
    // For example, currently, the value of GET_A_REQUEST of enum Action is 5. That means
    // we will add a request to the queue, if the value that the random number that we
    // generate is greater than or equal to ADD_A_REQUEST (which is zero) and less
    // than GET_A_REQUEST (which is 5). Therefore, the weight of adding a request is
    // 5/10 = 1/2 (we have 10 values in the interval of 0 and 9.) That is, 50 percent
    // of the times we add a request to the queue. On the other hand, 40% of the times
    // we remove a request from the queue and 10% of the times we inspect the queue to
    // determine if it is empty or not.

    // Please note that numTestsToGenerate bounds the number of requests that we
    // generate. Therefore, we will skip generating requests if we ever reach this
    // value.

    // This is a long function, however breaking it up into more functions would require
    // many arguments to be passed to helper functions. That is a trade off.

    auto *queue = new STQueue();
    srandom(getpid());

    int numRequestsGenerated = 0, numTestsRun = 0, numRequestsInTheQueue = 0, numSametrackgenerated = 0, numsametrackrequestinqueue = 0;
    int currentTrack = 0, currentSector = 0;
    double previousTrack = 0.0;

    while ( numTestsRun < numTestsToRun ) {
        Request *request = nullptr;
        int actionRange = (int) (random() % ACTION_RANGE);
        if (numRequestsGenerated < numRequestsToGenerate && actionRange >= ADD_A_REQUEST && actionRange < GET_A_REQUEST) { //creating our randomly generated set of requests
            std::cout << "Testing addRequest\n";
            request = generateRandomRequest();
            std::cout << "Adding the following request to the STQueue.\n";
            request->print();
            currentTrack = request->track();
            queue->addRequest(request, currentTrack, currentSector);
            //check queue if the track of the request we are currently trying to add to the queue already exsists
                //if it already exsists increment numSametrackgenerated by one and numsamestrackrequestinqueue by one
            numSametrackgenerated = numSametrackgenerated + queue->same_track_counter(currentTrack);
            numRequestsGenerated++;
            numRequestsInTheQueue++;
            numsametrackrequestinqueue++;
        } else if (actionRange < INSPECT_QUEUE) {
            std::cout << "Testing getRequest\n";
            if (queue->empty())
                std::cout << "STQueue is empty.\n";
            else {
                request = queue->getRequest();
                // try{
                //  request = queue->getRequest();
                // }catch(Request* request){
                //     cout<<"Opened a deleted request"<<endl;
                //     exit;
                // }
                
                
                if(request->track() == previousTrack){//if prev track is equal to the current track then decrement numsamestrackrequestinqueue by one
                    cout<<"Removing the following request which was found on the same track as the previous track from STQueue via getRequest.\n";
                    request->print();
             
                }
                else{
                    std::cout << "Removed the following request from the STQueue via getRequest.\n";
                    request->print();
                   

                }
                
                    previousTrack = request->track();
                    delete request;
                    request = nullptr;
                    cout<<numsametrackrequestinqueue--;

                    // request->track(0);
                    // delete request;
                    // request = nullptr; // We do not have a use for this request any longer.
                    // numRequestsInTheQueue--; 
            }
        } else {
            std::cout << "Testing whether the queue is empty or not.\n";
            if (numRequestsInTheQueue != 0 && queue->empty()) {
                std::cout << "STQueue::empty() returns true, but the queue should have " <<
                          numRequestsInTheQueue << " elements in it." << std::endl;
                exit(1);
            } else if (numRequestsInTheQueue == 0 && !queue->empty()) {
                std::cout << "STQueue::empty() returns false, but the queue should be empty." << std::endl;
                exit(1);
            } 
        }
        numTestsRun++;
    }

    while(! queue->empty() && numRequestsInTheQueue > 0) {//once we we have run reached number of tests to run
        std::cout << "Removed the following request from the STQueue after having tested the queue.\n";
        auto *request = queue->getRequest();
        request->print();
        request->track(0);
        cout<<"After inserting";
        request->print();
        delete request;
        request = nullptr;
        numRequestsInTheQueue--;
        cout<<"num req in the queue"<<numRequestsInTheQueue<<endl;
    }

   

    if( numRequestsInTheQueue > 0 ) {//if we have reached number of tests we can run and queue is empty we our count does not match how many add requests we made
        std::cout << "In the process of testing, the STQueue lost " << numRequestsInTheQueue <<
            ". This means the queue contains a bug!\n";
    } else if(numRequestsInTheQueue < 0) {
        std::cout << "In the process of testing, the STQueue did not remove " << -numRequestsInTheQueue <<
                  "requests as a result of getRequest having been called. This means the queue contains a bug!\n";
    }

    return queue;
}






int main(int argc, char *argv[]) {
    std::cout << "ST -- Main function.\n";
    const int randomTest = true;
    STQueue *queue = nullptr;
    
    if(randomTest){
        queue = createSTQueueFromRandomValues(50, 100);   
    }else{
        queue = createSTQueueFromInputFile(argc, argv);
    }
    
    delete queue;
    queue = nullptr;
    queue->print();

    return 0;
}
