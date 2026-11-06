
simple Scheduler
{
      parameters:
        //@display("i=block/dispatch");
        //volatile
        double schedulingPeriod @unit(ms) = default(1 ms);
        int gateSize;//me, dt

    gates:
        output txScheduling[gateSize];
        input rxInfo[gateSize];
}
