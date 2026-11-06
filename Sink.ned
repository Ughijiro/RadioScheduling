simple Sink
{
 parameters:
        int gateSize;
       // @display("i=block/sink");
      //  @signal[lifetime](type="simtime_t");
      //  @statistic[lifetime](title="lifetime of arrived jobs"; unit=s; record=vector,mean,max; interpolationmode=none);
    gates:
        input rxPackets[gateSize];

}
