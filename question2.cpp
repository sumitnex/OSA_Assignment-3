
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// Function to display frames
void printFrames(const vector<int>& frames) {
    for (int page : frames) {
        if (page != -1)
            cout << page << " ";
        else
            cout << "- ";
    }
}

// 1. FIFO Page Replacement
void fifo(const vector<int>& pages, int frameCount) {
    vector<int> frames(frameCount, -1);
    int pageFaults = 0, pageHits = 0;
    int insertIndex = 0;

    cout << "\n================ FIFO Page Replacement ================\n";
    cout << left << setw(8) << "Ref"
         << setw(16) << "Frames"
         << setw(10) << "Status" << endl;
    cout << "--------------------------------------------------------\n";

    for (int page : pages) {
        bool hit = false;

        for (int f : frames) {
            if (f == page) {
                hit = true;
                break;
            }
        }

        cout << left << setw(8) << page;

        if (hit) {
            pageHits++;
            cout << setw(16);
            printFrames(frames);
            cout << setw(10) << "Hit" << endl;
        } else {
            pageFaults++;
            frames[insertIndex] = page;
            insertIndex = (insertIndex + 1) % frameCount;

            cout << setw(16);
            printFrames(frames);
            cout << setw(10) << "Fault" << endl;
        }
    }

    cout << "--------------------------------------------------------\n";
    cout << "Total Page Faults : " << pageFaults << endl;
    cout << "Total Page Hits   : " << pageHits << endl;
}

// 2. LRU Page Replacement
void lru(const vector<int>& pages, int frameCount) {
    vector<int> frames(frameCount, -1);
    vector<int> lastUsed(frameCount, -1);
    int pageFaults = 0, pageHits = 0;

    cout << "\n================ LRU Page Replacement ================\n";
    cout << left << setw(8) << "Ref"
         << setw(16) << "Frames"
         << setw(10) << "Status" << endl;
    cout << "--------------------------------------------------------\n";

    for (int t = 0; t < (int)pages.size(); t++) {
        int page = pages[t];
        int frameIdx = -1;

        for (int i = 0; i < frameCount; i++) {
            if (frames[i] == page) {
                frameIdx = i;
                break;
            }
        }

        cout << left << setw(8) << page;

        if (frameIdx != -1) {
            pageHits++;
            lastUsed[frameIdx] = t;

            cout << setw(16);
            printFrames(frames);
            cout << setw(10) << "Hit" << endl;
        } else {
            pageFaults++;
            int replaceIdx = -1;

            // Find an empty frame
            for (int i = 0; i < frameCount; i++) {
                if (frames[i] == -1) {
                    replaceIdx = i;
                    break;
                }
            }

            // Replace least recently used page
            if (replaceIdx == -1) {
                int leastTime = lastUsed[0];
                replaceIdx = 0;

                for (int i = 1; i < frameCount; i++) {
                    if (lastUsed[i] < leastTime) {
                        leastTime = lastUsed[i];
                        replaceIdx = i;
                    }
                }
            }

            frames[replaceIdx] = page;
            lastUsed[replaceIdx] = t;

            cout << setw(16);
            printFrames(frames);
            cout << setw(10) << "Fault" << endl;
        }
    }

    cout << "--------------------------------------------------------\n";
    cout << "Total Page Faults : " << pageFaults << endl;
    cout << "Total Page Hits   : " << pageHits << endl;
}

// 3. Optimal Page Replacement
void optimal(const vector<int>& pages, int frameCount) {
    vector<int> frames(frameCount, -1);
    int pageFaults = 0, pageHits = 0;

    cout << "\n================ Optimal Page Replacement ================\n";
    cout << left << setw(8) << "Ref"
         << setw(16) << "Frames"
         << setw(10) << "Status" << endl;
    cout << "----------------------------------------------------------\n";

    for (int t = 0; t < (int)pages.size(); t++) {
        int page = pages[t];
        bool hit = false;

        for (int f : frames) {
            if (f == page) {
                hit = true;
                break;
            }
        }

        cout << left << setw(8) << page;

        if (hit) {
            pageHits++;
            cout << setw(16);
            printFrames(frames);
            cout << setw(10) << "Hit" << endl;
        } else {
            pageFaults++;
            int replaceIdx = -1;

            // Find an empty frame
            for (int i = 0; i < frameCount; i++) {
                if (frames[i] == -1) {
                    replaceIdx = i;
                    break;
                }
            }

            // Replace the page used farthest in the future
            if (replaceIdx == -1) {
                int farthest = t;

                for (int i = 0; i < frameCount; i++) {
                    int nextUse = -1;

                    for (int j = t + 1;
                         j < (int)pages.size(); j++) {
                        if (frames[i] == pages[j]) {
                            nextUse = j;
                            break;
                        }
                    }

                    // Page is not used again
                    if (nextUse == -1) {
                        replaceIdx = i;
                        break;
                    }

                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIdx = i;
                    }
                }
            }

            frames[replaceIdx] = page;

            cout << setw(16);
            printFrames(frames);
            cout << setw(10) << "Fault" << endl;
        }
    }

    cout << "----------------------------------------------------------\n";
    cout << "Total Page Faults : " << pageFaults << endl;
    cout << "Total Page Hits   : " << pageHits << endl;
}

int main() {
    vector<int> pages = {1, 2, 3, 2, 4, 1, 5, 2};
    int frameCount = 3;

    cout << "Page Reference String : 1, 2, 3, 2, 4, 1, 5, 2\n";
    cout << "Total Page Frames     : 3\n";

    fifo(pages, frameCount);
    lru(pages, frameCount);
    optimal(pages, frameCount);

    return 0;
}
