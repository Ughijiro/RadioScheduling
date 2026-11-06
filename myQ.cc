#include "myQ.h"

Define_Module(MyQ);

void MyQ::initialize()
{
    queue.setName("queue");
}

void MyQ::handleMessage(cMessage *msg)

{

    int ql; //=9;

    if (msg->arrivedOn("rxPackets")){
        queue.insert(msg);
    } else if (msg->arrivedOn("rxScheduling")) {
        // Read the number of allocated radio blocks
        int nrOfRadioBlocks = msg->par("nrBlocks").longValue();
        delete msg;
        // Send at most one packet per allocated block
        for (int j = 0; j < nrOfRadioBlocks && !queue.isEmpty(); j++) {
            cMessage *packet = (cMessage *)queue.pop();
            send(packet, "txPackets");
        }
    }
    ql = queue.getLength();


    cMessage *qInfo = new cMessage("qInfo");
    qInfo->addPar("ql_info");
    qInfo->par("ql_info").setLongValue(ql);//ql instead of 2

    //only for test

    int i =  getParentModule()->getIndex();

    long ql_info_tst = qInfo->par("ql_info");
    EV << "ql[" << i<<"] = " << ql << " ql_info_tst = " << ql_info_tst << endl;
    send(qInfo, "txInfo");

    /* Communication between modules using parameters
    ql = queue.getLength();
    cPar&  qlpar = par("qlp");
    qlpar.setIntValue(ql);
    //next 2 statements only for debug
    int qt = par("qlp").intValue();
    EV << "qt= "<<qt <<endl;
    */

}
