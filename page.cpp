
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> pages;
int n, size;

void result(string name, int faults) {
    cout << name << " Page Faults = " << faults << "\n";
}

// FIFO
void fifo() {
    vector<int> f(size, -1);
    int pos = 0, faults = 0;

    for (int x : pages) {
        if (find(f.begin(), f.end(), x) == f.end()) {
            f[pos] = x;
            pos = (pos + 1) % size;
            faults++;
        }
    }
    result("FIFO", faults);
}

// LRU
void lru() {
    vector<int> f(size, -1), last(size, -1);
    int faults = 0;

    for (int i = 0; i < n; i++) {
        int pos = -1;

        for (int j = 0; j < size; j++)
            if (f[j] == pages[i])
                pos = j;

        if (pos == -1) {
            pos = 0;
            for (int j = 1; j < size; j++)
                if (last[j] < last[pos])
                    pos = j;    


            f[pos] = pages[i];
            faults++;
        }
        last[pos] = i;
    }
    result("LRU", faults);
}

// OPTIMAL
void optimal() {
    vector<int> f(size, -1);
    int faults = 0;

    for (int i = 0; i < n; i++) {
        if (find(f.begin(), f.end(), pages[i]) != f.end())
            continue;

        int pos = 0, farthest = -1;

        for (int j = 0; j < size; j++) {
            int k;
            for (k = i + 1; k < n; k++)
                if (f[j] == pages[k])
                    break;

            if (k > farthest) {
                farthest = k;
                pos = j;
            }
        }

        f[pos] = pages[i];
        faults++;
    }
    result("Optimal", faults); 
}

int main() {
    cout << "Enter number of pages: ";
    cin >> n;

    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pages.push_back(x);
    }

    cout << "Enter number of frames: ";
    cin >> size;

    if (n <= 0 || size <= 0) {
        cout << "Invalid input\n";
        return 1;
    }

    int choice;
    do {
        cout << "\n1.FIFO  2.LRU  3.Optimal  5.Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fifo(); break;
            case 2: lru(); break;
            case 3: optimal(); break;
            case 5: break;
            default: cout << "Invalid choice\n";
        }
    } while (choice != 5);

    return 0;
}