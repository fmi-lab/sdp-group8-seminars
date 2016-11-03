#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

#include <queue>
#include <iostream>

class WaitingQueue
{
    public:
        WaitingQueue(int);
        void reset();
        int getNumWaiting() const;
        int getIdleTime() const;
        void enqueue(const std::string&);
        bool tick(std::string&);
    protected:
    private:
        std::queue<std::string> waiting;
        int ticksPerPerson;
        int remainingTicks;
        int idleTime;
        bool busy;
};

#endif // WAITINGQUEUE_H
