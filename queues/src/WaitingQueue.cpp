#include "WaitingQueue.h"

WaitingQueue::WaitingQueue(int ticksPerPerson)
    :ticksPerPerson(ticksPerPerson), remainingTicks(0), idleTime(0), busy(false)
{ }

void WaitingQueue::reset() {
    while(!waiting.empty()) {
        waiting.pop();
    }
    remainingTicks = 0;
    idleTime = 0;
}

int WaitingQueue::getNumWaiting() const {
    return waiting.size();
}

int WaitingQueue::getIdleTime() const {
    return idleTime;
}

void WaitingQueue::enqueue(const std::string& client) {
    waiting.push(client);
}

bool WaitingQueue::tick(std::string& servicedClient) {
    if (!busy) {
        if (waiting.empty()) {
            idleTime++;
        } else {
            std::cout << "Begin service for " << waiting.front() << std::endl;
            remainingTicks = ticksPerPerson;
            busy = true;
        }
        return false;
    } else {
        remainingTicks--;
        if (remainingTicks == 0) {
            // done with this person
            servicedClient = waiting.front();
            waiting.pop();
            busy = false;
            return true;
        }
        return false;
    }
}
