#include "Scheduler.h"

Define_Module(Scheduler);



Scheduler::Scheduler()
{
    selfMsg = nullptr;
}

Scheduler::~Scheduler()
{
    cancelAndDelete(selfMsg);
}


void Scheduler::initialize()
{
    NrUsers = par("gateSize").intValue();
    NrOfChannels = 10;//read from omnetpp.ini

    for (int i = 0; i < NrUsers; i++) {
        userWeights[i] = 1;
    }

    userWeights[2] = 2; // user 2 e mai smecher

    selfMsg = new cMessage("selfMsg");
    for(int i = 0; i < 10; i++){
           q[i] = 0;
           lag[i] = 0;
           //NrBlocks[i]=0;
    }
    scheduleAt(simTime(), selfMsg);


}

void Scheduler::handleMessage(cMessage *msg)
{
   // int q[NrUsers];
 //   int NrBlocks[Nrusers];

    /*
    for(int j=0;j<NrUsers; j++){
        q[j]= getParentModule()->getSubmodule("user",j)->getSubmodule("myqq")->par("qlp");
        EV << "q["<<j<<"]= " << q[j] <<endl;
    }
     */


    //int userWeights[NrUsers];
    for(int i =0; i<NrUsers;i++){

    if (msg->arrivedOn("rxInfo", i)){
        q[i]= msg->par("ql_info");
        EV << "Update: q["<<i<<"]= " << q[i] <<endl;
        delete(msg);
        return;
    }
    }

        if (msg == selfMsg){

          //here comes the scheduling algorithm !!!
            // Reset the number of allocated blocks
            bool idealAvailable[10];
            bool realAvailable[10];

            for (int i = 0; i < NrUsers; i++) {
                idealAvailable[i] = true;
                realAvailable[i] = true;

                if (i == 1 && simTime() >= 0.020 && simTime() < 0.040) {
                    realAvailable[i] = false;
                }
            }

            calculateWRR(idealBlocks, idealAvailable, userWeights);
            calculateWRR(NrBlocks, realAvailable, userWeights);

            for (int i = 0; i < NrUsers; i++) {
                lag[i] += idealBlocks[i] - NrBlocks[i];
            }

            for (int i = 0; i < NrUsers; i++) {
                EV << "User " << i
                   << " Ideal: " << idealBlocks[i]
                   << " Real: " << NrBlocks[i]
                   << " LAG: " << lag[i]
                   << endl;
            }

            for(int i =0;i<NrUsers;i++){

        //finds out the length of each queue !!
                if(NrBlocks[i]>0){
                    cMessage *cmd = new cMessage("cmd");

                    // q[i]= q[i]-NrBlocks[i];
                    // EV << "Decrease: q["<<i<<"]= " << q[i] <<endl;
                    cmd->addPar("nrBlocks");
                    cmd->par("nrBlocks").setLongValue(NrBlocks[i]);
                    //set parameter value, e.g., nr of blocks to be sent from the queue by user i
                    //
                    send(cmd,"txScheduling",i);
                }
          //  double xtime = simTime().dbl();
            }
            scheduleAt(simTime() + par("schedulingPeriod").doubleValueInUnit("s"), selfMsg);

    }

}

void Scheduler::calculateWRR(int blocks[], const bool canReceive[], const int weights[])
{
    for (int i = 0; i < NrUsers; i++) {
        blocks[i] = 0;
    }

    int remainingBlocks = NrOfChannels;

    while (remainingBlocks > 0) {
        bool allocated = false;

        for (int i = 0; i < NrUsers && remainingBlocks > 0; i++) {

            if (!canReceive[i]) {
                continue;
            }

            for (int j = 0; j < weights[i] && remainingBlocks > 0; j++) {
                if (blocks[i] < q[i]) {
                    blocks[i]++;
                    remainingBlocks--;
                    allocated = true;
                }
            }
        }

        if (!allocated) {
            break;
        }
    }
}
