#include <iostream>
#include <vector>

using namespace std;

struct Block {
    int size;
    bool allocated;  // If block is allocated or not
};

struct Process {
    int size;
    int allocatedBlock;  // The index of the allocated block (-1 if not allocated)
};

void firstFit(vector<Block>& blocks, int numBlocks, vector<Process>& processes, int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        processes[i].allocatedBlock = -1;  // Initially, no process is allocated
        for (int j = 0; j < numBlocks; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size) {
                processes[i].allocatedBlock = j;
                blocks[j].allocated = true;
                break;
            }
        }
    }
}

void bestFit(vector<Block>& blocks, int numBlocks, vector<Process>& processes, int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        int bestIdx = -1;
        int minSize = 1e9;  // Initially setting to a large number
        for (int j = 0; j < numBlocks; j++) {
            if (!blocks[j].allocated && blocks[j].size >= processes[i].size && blocks[j].size < minSize) {
                bestIdx = j;
                minSize = blocks[j].size;
            }
        }

        if (bestIdx != -1) {
            processes[i].allocatedBlock = bestIdx;
            blocks[bestIdx].allocated = true;
        }
    }
}

void printResults(vector<Process>& processes, int numProcesses) {
    cout << "\nProcess Allocation Results:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "Process " << i + 1 << " (Size " << processes[i].size << ") -> ";
        if (processes[i].allocatedBlock != -1)
            cout << "Block " << processes[i].allocatedBlock + 1 << "\n";
        else
            cout << "Not Allocated\n";
    }
}

int main() {
    int numBlocks, numProcesses;

    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;
    vector<Block> blocks(numBlocks);

    cout << "Enter block sizes:\n";
    for (int i = 0; i < numBlocks; i++) {
        cin >> blocks[i].size;
        blocks[i].allocated = false;  // Initially, no blocks are allocated
    }

    cout << "Enter number of processes: ";
    cin >> numProcesses;
    vector<Process> processes(numProcesses);

    cout << "Enter process sizes:\n";
    for (int i = 0; i < numProcesses; i++) {
        cin >> processes[i].size;
        processes[i].allocatedBlock = -1;  // Initially, no processes are allocated
    }

    int choice;
    do {
        // Reset allocation status
        for (int i = 0; i < numBlocks; i++) blocks[i].allocated = false;
        for (int i = 0; i < numProcesses; i++) processes[i].allocatedBlock = -1;

        cout << "\nMemory Allocation Techniques:\n";
        cout << "1. First Fit\n2. Best Fit\n3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                firstFit(blocks, numBlocks, processes, numProcesses);
                printResults(processes, numProcesses);
                break;
            case 2:
                bestFit(blocks, numBlocks, processes, numProcesses);
                printResults(processes, numProcesses);
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}

