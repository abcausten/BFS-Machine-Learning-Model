# Missionaries and Cannibals: BFS Solver (C++)

A C++ solution to the classic Missionaries and Cannibals puzzle using Breadth-First Search (BFS). Because BFS explores states level by level, it returns a **shortest** sequence of boat crossings.

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
| 1    | 1 cannibal |
| 2    | 2 cannibals |
| 10   | 1 missionary |
| 20   | 2 missionaries |
| 11   | 1 missionary + 1 cannibal |

## Build and Run

```bash
g++ -std=c++17 -o mc_bfs BFS Search Algorithm.cpp
./mc_bfs
```

## Example Output

```
[paste your program's output here]
```

BFS finds the optimal solution for the standard puzzle, which takes **11 crossings**. Check this against your output.

## Complexity

The state space is small (at most `(M+1) * (C+1) * 2` states), so BFS runs quickly. Time and space are both O(number of states).

## Author

[Your Name]
