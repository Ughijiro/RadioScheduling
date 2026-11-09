
# Radio Scheduling - OMNeT++

CAD project: **A Scheduling Model for a Radio System with Location Dependent Errors**

Developed using OMNeT++ 6.4.0, based on the professor's starter code.

## Project Overview

We simulate a radio system where a scheduler distributes a limited number of radio blocks between users.

Main components:
- `Source` - generates packets.
- `MyQ` - stores packets in each user's queue.
- `Scheduler` - decides how many blocks each user receives.
- `Sink` - receives transmitted packets.

## Current Implementation

- 3 users and 10 available radio blocks.
- Scheduling every 1 ms.
- Weighted Round Robin (WRR) algorithm.
- User weights: `[1, 1, 2]` (User 2 has higher priority).
- Block allocation depends on user weights and queue lengths.

### Bad Radio Connection

User 1 has a simulated bad connection between 20 ms and 40 ms.

During this interval:
- User 1 receives 0 blocks.
- The other users share the available blocks.
- After 40 ms, User 1 can receive blocks again.

### LAG and Recovery

We calculate two allocations:
- `idealBlocks` - allocation assuming all users have a good connection.
- `NrBlocks` - actual allocation considering the bad connection.

LAG represents the accumulated difference:

`lag[i] += idealBlocks[i] - NrBlocks[i]`

When a user has positive LAG and a working connection, their WRR weight temporarily increases by 1.

This allows the user to recover the missing blocks over time.

When LAG reaches 0, the normal weight is restored.

## Test Results

Simulation tested up to 105 ms.

| Time | User 1 LAG | Result |
|------|------------|--------|
| 19 ms | 0 | Normal connection |
| 20 ms | 3 | Connection lost |
| 39 ms | 60 | Maximum LAG |
| 40 ms | 59 | Recovery starts |
| 50 ms | 49 | Recovery continues |
| 99 ms | 0 | Recovery completed |
| 100 ms | 0 | Normal WRR restored |

The simulation runs without build errors.

## What Is Left To Do

- Move hardcoded values into `omnetpp.ini`.
- Improve support for a configurable number of users.
- Improve the ideal model (separate queue tracking).
- Compare normal WRR with adaptive WRR.
- Add statistics and graphs.
- Perform final testing and documentation.

## Notes

The current bad connection is simulated using a fixed time interval, not a distance-based probability model.

The ideal and real allocations currently use the same queue lengths.

The project is not finished yet, but WRR, LAG calculation and adaptive recovery have been implemented and tested.

The project uses the professor's starter code and has been developed with AI assistance, which must be disclosed according to the course requirements.
