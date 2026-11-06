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
    selfMsg = new cMessage("selfMsg");
    for(int i=0; i<10;i++){
           q[i]=0;
         //  NrBlocks[i]=0;
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


    int userWeights[NrUsers];
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
            for(int i =0;i<NrUsers;i++){
                NrBlocks[i]=1;//you have to change this !!!
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
