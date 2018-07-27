#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    std::cout << "Connecting to the hello world server...\n";
    socket.connect("tcp://localhost:5555");

    for (int i = 0; i < 10; ++i) {
        zmq::message_t request(5);
        mempcpy(request.data(), "Hello", 5);

        std::cout << "Sending Hello " << i << "...\n";
        socket.send(request);

        zmq::message_t reply;
        socket.recv(&reply);
        std::cout << "Received " << (char*) reply.data() << " ... " << i << std::endl;
    }
    return 0;
}