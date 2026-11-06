# Radio Scheduling

CAD project developed in OMNeT++ 6.4.0.

**Project topic:** A scheduling model for a radio system with location dependent errors.

## Project Files

- **RadioSch.ned** – Defines the network and connects the scheduler, users and sink.
- **user.ned** – Defines each user, containing a packet generator and a queue.
- **Source.ned / Source.cc / Source.h** – Generates packets at random time intervals.
- **myQ.ned / myQ.cc / myQ.h** – Stores packets in a queue, sends packets when allowed by the scheduler and reports the queue length.
- **Scheduler.ned / Scheduler.cc / Scheduler.h** – Receives queue information and decides how many packets each user can send.
- **Sink.ned / Sink.cc / Sink.h** – Receives transmitted packets.
- **omnetpp.ini** – Contains the simulation settings, such as the number of users and packet generation interval.

## How It Works

1. Source generates packets.
2. MyQ stores the packets in a queue.
3. MyQ sends the queue length to Scheduler.
4. Scheduler sends commands to users.
5. MyQ sends the allowed number of packets to Sink.

## Initial Code Fixes

The project started from code provided by the professor. Before adding our own features, we made a few corrections:

- **RadioSch.ned:** Fixed the `gateSize` parameter reference using `parent.usersCount`.
- **Source.cc:** Fixed time conversion so packet generation uses the correct milliseconds.
- **Scheduler.cc:** Fixed the scheduling period from seconds to milliseconds and added `return` after deleting received queue information messages.
- **myQ.cc:** Changed the queue behavior so it sends only the number of packets allowed by the scheduler, instead of sending the entire queue.

## Current Status

The project builds and runs successfully with 3 users.

- Packets are generated and stored in queues.
- Scheduling runs every 1 ms.
- Each user currently receives 1 radio block per scheduling cycle.
- Sink successfully receives transmitted packets.

## Next Steps

- Implement a scheduling algorithm for the available radio channels.
- Add location-dependent transmission errors.
- Collect statistics and compare simulation results.
