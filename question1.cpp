
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Function to display allocation results
void displayResults(const string& strategyName,
                    const vector<int>& processSize,
                    const vector<int>& allocation,
                    const vector<int>& remainingBlockSize,
                    int initialTotalBlockMem) {
    int m = processSize.size();
    int allocatedCount = 0;
    int allocatedMemorySum = 0;

    cout << "\n================ " << strategyName
         << " Allocation Table ================\n";

    cout << left << setw(12) << "Process No."
         << setw(16) << "Process Size"
         << setw(14) << "Block Allocated" << endl;

    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < m; i++) {
        cout << left << setw(12) << (i + 1)
             << setw(16) << processSize[i];

        if (allocation[i] != -1) {
            cout << "Block " << (allocation[i] + 1) << endl;
            allocatedCount++;
            allocatedMemorySum += processSize[i];
        } else {
            cout << "Not Allocated" << endl;
        }
    }

    int remainingFreeMemory = 0;
    for (int size : remainingBlockSize) {
        remainingFreeMemory += size;
    }

    double memoryUtilization =
        ((double)allocatedMemorySum / initialTotalBlockMem) * 100.0;

    cout << "---------------------------------------------------------\n";
    cout << "Successfully Allocated Processes : "
         << allocatedCount << " / " << m << endl;
    cout << "Remaining Free Memory            : "
         << remainingFreeMemory << " KB" << endl;

    cout << fixed << setprecision(2);
    cout << "Memory Utilization                : "
         << memoryUtilization << " %" << endl;
}

// 1. First Fit Algorithm
void firstFit(vector<int> blockSize,
              vector<int> processSize, int totalBlockMem) {
    int m = processSize.size();
    int n = blockSize.size();
    vector<int> allocation(m, -1);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    displayResults("First Fit", processSize,
                   allocation, blockSize, totalBlockMem);
}

// 2. Best Fit Algorithm
void bestFit(vector<int> blockSize,
             vector<int> processSize, int totalBlockMem) {
    int m = processSize.size();
    int n = blockSize.size();
    vector<int> allocation(m, -1);

    for (int i = 0; i < m; i++) {
        int bestIdx = -1;

        for (int j = 0; j < n; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 ||
                    blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    displayResults("Best Fit", processSize,
                   allocation, blockSize, totalBlockMem);
}

// 3. Worst Fit Algorithm
void worstFit(vector<int> blockSize,
              vector<int> processSize, int totalBlockMem) {
    int m = processSize.size();
    int n = blockSize.size();
    vector<int> allocation(m, -1);

    for (int i = 0; i < m; i++) {
        int worstIdx = -1;

        for (int j = 0; j < n; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 ||
                    blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    displayResults("Worst Fit", processSize,
                   allocation, blockSize, totalBlockMem);
}

int main() {
    vector<int> blockSize = {100, 500, 200, 300, 600};
    vector<int> processSize = {212, 417, 112, 426};

    int totalBlockMem = 0;
    for (int size : blockSize) {
        totalBlockMem += size;
    }

    cout << "Total Physical Memory Available: "
         << totalBlockMem << " KB\n";
    cout << "Blocks Available: 100 KB, 500 KB, 200 KB, "
            "300 KB, 600 KB\n";
    cout << "Process Requests: P1(212 KB), P2(417 KB), "
            "P3(112 KB), P4(426 KB)\n";

    firstFit(blockSize, processSize, totalBlockMem);
    bestFit(blockSize, processSize, totalBlockMem);
    worstFit(blockSize, processSize, totalBlockMem);

    return 0;
}
