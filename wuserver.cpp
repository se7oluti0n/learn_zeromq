#include <zmq.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "zhelpers.hpp"

int main() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("ipc://weathers.ipc");

    srandom((unsigned) time(NULL));

    while(1) {
        int zipcode, temperature, relhumidity;

        //  Get values that will fool the boss
        zipcode     = within (100000);
        temperature = within (215) - 80;
        relhumidity = within (50) + 10;

        zmq::message_t message(20);
        snprintf ((char *) message.data(), 20 ,
        	"%05d %d %d", zipcode, temperature, relhumidity);

        publisher.send(message);
    }
}