#ifndef __SCHED_TST_SCHEDULER_H_
#define __SCHED_TST_SCHEDULER_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Scheduler : public cSimpleModule
{
public:
    Scheduler();
    ~Scheduler();
private:
    cMessage *selfMsg;
    int NrUsers;
    int NrOfChannels;
    int userWeights[10];
    int q[10];// queues' lengths. NrUsers schould be <= 10 !!!
    int NrBlocks[10];
    int idealBlocks[10];
    int lag[10];
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void calculateWRR(int blocks[], const bool canReceive[], const int weights[]);
};

#endif
