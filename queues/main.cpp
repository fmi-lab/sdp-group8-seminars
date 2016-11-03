#include <iostream>
#include <queue>
#include <sstream> // for stringstream
#include <stdio.h> // for sprintf
#include <stdlib.h> // for rand()
#include <time.h>
#include "WaitingQueue.h"

std::string getClientName(int clientIdx) {
    // concatenate string with a number using string stream
    std::stringstream temp;
    temp << "Client " << clientIdx;
    return temp.str();
    // alternative method:
    // char name[13]; // this can only hold the string "Client " + up to 5 digits!
    // sprintf(name, "%s %d", "Client", clientIdx);
    // return name;
}

int main () {
    // uncomment this line to get different results on each run
    // srand(time(NULL));
    WaitingQueue ticketDesk(30);
    WaitingQueue popcorn(90);
    WaitingQueue glasses(15);
    int peopleCount = 0;
    int numServiced = 0;
    for (int i = 0; i < 30*60; i++) {
        bool hasMoved;
        std::string clientTemp;
        if (i % 60 == 0) {
            std::cout << std::endl << "Begin minute " << i / 60 + 1 << std::endl;
        }
        if (i % 120 == 0 && i < 15*60) {
            // two minutes have passed
            // rand() % 10 is in the [0, 9] range
            int numNewcomers = rand() % 10 + 1;
            std::cout << "NEW CROWD SIZE: " << numNewcomers << std::endl;
            for (int j = 0; j < numNewcomers; j++) {
                peopleCount++;
                ticketDesk.enqueue(getClientName(peopleCount));
            }
        }
        hasMoved = ticketDesk.tick(clientTemp);
        if (hasMoved) {
            std::cout << clientTemp << " leaves the ticket queue." << std::endl;
            // 70% chance the client will go for popcorn
            if ((rand()+1) % 10 < 7) {
                std::cout << clientTemp << " enters the popcorn queue." << std::endl;
                popcorn.enqueue(clientTemp);
            } else {
                std::cout << clientTemp << " enters the 3D glasses queue." << std::endl;
                glasses.enqueue(clientTemp);
            }
        }
        hasMoved = popcorn.tick(clientTemp);
        if (hasMoved) {
            std::cout << clientTemp << "leaves the popcorn queue and enters the 3D glasses queue." << std::endl;
            glasses.enqueue(clientTemp);
        }
        hasMoved = glasses.tick(clientTemp);
        if (hasMoved) {
            std::cout << "Client " << clientTemp <<" successfully reached the movie hall!" << std::endl;
            numServiced++;
        }
    }
    std::cout << "Tickets idle time: " << ticketDesk.getIdleTime() << std::endl;
    std::cout << "People left in ticket queue: " << ticketDesk.getNumWaiting() << std::endl;

    std::cout << "Popcorn idle time: " << popcorn.getIdleTime() << std::endl;
    std::cout << "People left in popcorn queue: " << popcorn.getNumWaiting() << std::endl;

    std::cout << "Glasses idle time: " << glasses.getIdleTime() << std::endl;
    std::cout << "People left in glasses queue: " << glasses.getNumWaiting() << std::endl;

    std::cout << "Serviced people / total people: " << numServiced << "/" << peopleCount << std::endl;
    return 0;
}
