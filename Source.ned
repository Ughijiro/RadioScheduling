simple Source
{
     parameters:
         double sendIaTime @unit(ms) = default(10 ms);
        //volatile double generatorPeriod @unit(ms) = default(100ms);
      //  @display("i=block/source");
    gates:
        output txPackets;
}
