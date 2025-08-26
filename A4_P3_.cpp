#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cstdlib>

using namespace std;

struct PuzzleState {
    vector<int> tiles;
    int movesMade;
    int priority;

    PuzzleState(vector<int> tileConfig, int moves) : tiles(tileConfig), movesMade(moves) {
        priority = movesMade + calculateManhattanDistance();
    }

    int calculateManhattanDistance() const {
        int totalDistance = 0;
        for (int index = 0; index < 9; index++) {
            if (tiles[index] == 0) continue;
            int tileValue = tiles[index];
            int targetRow = (tileValue - 1) / 3;
            int targetCol = (tileValue - 1) % 3;
            int currentRow = index / 3;
            int currentCol = index % 3;
            totalDistance += abs(targetRow - currentRow) + abs(targetCol - currentCol);
        }
        return totalDistance;
    }

    bool operator<(const PuzzleState& other) const {
        return priority > other.priority;
    }
};

bool isTargetConfiguration(const vector<int>& tileConfig) {
    vector<int> target = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    return tileConfig == target;
}

vector<pair<int, int>> moveDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int findMinimumMoves(vector<int>& initialConfig) {
    priority_queue<PuzzleState> stateQueue;
    set<vector<int>> visitedStates;

    PuzzleState initialState(initialConfig, 0);
    stateQueue.push(initialState);
    visitedStates.insert(initialConfig);

    while (!stateQueue.empty()) {
        PuzzleState currentState = stateQueue.top();
        stateQueue.pop();

        if (isTargetConfiguration(currentState.tiles)) {
            return currentState.movesMade;
        }

        int blankTileIndex = 0;
        for (int index = 0; index < 9; index++) {
            if (currentState.tiles[index] == 0) {
                blankTileIndex = index;
                break;
            }
        }

        int blankRow = blankTileIndex / 3;
        int blankCol = blankTileIndex % 3;

        for (const auto& direction : moveDirections) {
            int newRow = blankRow + direction.first;
            int newCol = blankCol + direction.second;

            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                int newTileIndex = newRow * 3 + newCol;

                vector<int> newTileConfig = currentState.tiles;
                swap(newTileConfig[blankTileIndex], newTileConfig[newTileIndex]);

                if (visitedStates.find(newTileConfig) == visitedStates.end()) {
                    visitedStates.insert(newTileConfig);
                    PuzzleState nextState(newTileConfig, currentState.movesMade + 1);
                    stateQueue.push(nextState);
                }
            }
        }
    }

    return -1;
}

int main() {
    vector<int> initialTiles(9);
    for (int index = 0; index < 9; index++) {
        cin >> initialTiles[index];
    }

    int minimumMoves = findMinimumMoves(initialTiles);
    cout << minimumMoves << endl;

    return 0;
}