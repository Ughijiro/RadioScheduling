#include "Source.h"

Define_Module(Source);

Source::Source()
{
    sendMessageEvent = nullptr;
}

Source::~Source()
{
    cancelAndDelete(sendMessageEvent);
}

void Source::initialize()
{
    sendMessageEvent = new cMessage("sendMessageEvent");
    scheduleAt(simTime(), sendMessageEvent);
}

void Source::handleMessage(cMessage *msg)


{
    ASSERT(msg == sendMessageEvent);
//for(j=0;j<nrPackets;j++){
    cMessage *job = new cMessage("job");
    //the "job" message can have a parameter PacketLength !
    send(job, "txPackets");

//}
    //end for

    double sendingTime;
    sendingTime = par("sendIaTime").doubleValueInUnit("s");

   // if(simTime() >= MAX_SiM) endSimulation();
    //MAX_SiM se pune in ini si citeste de acolo si trebuie sa fie de cel putin 1000 de ori mai mare
    // decat sendingTime pt netwload 80% (ideal de 10 mii de ori mai mare)


    //scheduleAt(simTime()+ exponential(sendingTime));

    // sendingTime = function(network load)

    /*netwload = data_generated/ transfer_rate
     *
     * data_generated = nrUsers* nrPackets *PacketLength / sendingTime
     * PacketLength = 1
     *
     * transfer_rate = nr_of_channels/schedulingCycle ;
     * schedulingCycle = 1 ms
     *
     * netwload = (nrUsers*nrPackets*PacketLength*schedulingCycle)/(sendingTime*nr_of_channels)
     *
     *sendingTime =  (nrUsers*nrPackets*PacketLength*schedulingCycle)/(netwload*nr_of_channels)
     *
     * */


    scheduleAt(simTime()+ exponential(sendingTime), sendMessageEvent);

    //scheduleAt(simTime()+par("sendIaTime").doubleValue(), sendMessageEvent);
}


/*
void Source::initialize()
{
    // TODO - Generated method body
}

void Source::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}
*/
