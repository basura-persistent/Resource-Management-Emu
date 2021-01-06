cmake_minimum_required(VERSION 3.12)
project(DiskSim.x)

set(CMAKE_CXX_STANDARD 17)

add_executable(fcfs.x FCFS_Queue/main.cpp FCFS_Queue/FCFSQueue.cpp FCFS_Queue/FCFSQueueNode.cpp CommonFiles/Request.cpp)
add_executable(st.x ST_Queue/main.cpp CommonFiles/Request.cpp)