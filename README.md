# Missionaries and Cannibals: BFS Solver (C++)
A C++ solution I built in Fall 2025 to the classic Missionaries and Cannibals puzzle using Breadth-First Search (BFS). 

## The Problem

Three missionaries and three cannibals are on one side of a river with a boat that holds one or two people. Move everyone to the other side without ever leaving missionaries outnumbered by cannibals on either bank (unless there are no missionaries there).

## Approach

**State:** `(missionaries on left bank, cannibals on left bank, boat side)`. The right bank is derived from the totals.

**Initial state:** `(3, 3, left)`  **Goal state:** `(0, 0, right)`

**Valid state:** on each bank, either there are no missionaries or missionaries >= cannibals.

**Search:**
1. Start from the initial state in a queue.
2. Expand each state by trying every legal boat load.
3. Skip invalid states and states already visited.
4. Store each state's parent and the action that led to it.
5. When the goal is reached, backtrack through the parents to rebuild the action list.

**Action encoding** (returned by `vector<int> breadth_first_searchMC()`):

| Code | Boat contents |
|------|---------------|
| `1` / `-1` | 1 cannibal |
| `2` / `-2` | 2 cannibals |
| `10` / `-10` | 1 missionary |
| `20` / `-20` | 2 missionaries |
| `11` / `-11` | 1 missionary + 1 cannibal |

A **negative** code means the boat is leaving the original side, and a **positive** code means it is returning.

### Algorithm

1. Start with the initial node `{boat on original side, 3 missionaries, 3 cannibals}` in a FIFO `frontier` queue.
2. Pop a node and call `Expand` to generate every legal child (one per boat load).
3. `validState` rejects states with negative counts or where cannibals outnumber missionaries on either bank (when missionaries are present).
4. If a child is the goal, stop and call `trace`.
5. Otherwise, if the child's state has not been reached before, add it to `reached` and the `frontier`.
6. `trace` follows `parent` links back to the root and reverses the list, giving the path from start to goal.

## Build and Run

```bash
g++ -std=c++17 -o mc_bfs BFS Search Algorithm.cpp
./mc_bfs
```
On Windows, run `mc_bfs.exe`.

## Example Output
This is a sample of one of the steps in the process in which the program will take 11 crossings, moving between 12 states to match the optimal solution.

```
\__/   CC
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        MMM C

Next step : -2
```

## Complexity

The state space is small (at most 32 states), so BFS runs quickly. 

