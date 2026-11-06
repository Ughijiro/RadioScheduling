import MyQ;
import Source;

module User
{
    parameters:
    	//@display("i=block/user");

   // @display("bgb=90,160");

    gates:
        output txPackets;
        output txInfo;
        input rxScheduling;

    submodules:
        generator: Source;

        myqq: MyQ;

    connections:
        rxScheduling --> myqq.rxScheduling;
        generator.txPackets --> myqq.rxPackets;
        myqq.txPackets --> txPackets;
        myqq.txInfo --> txInfo;

}
