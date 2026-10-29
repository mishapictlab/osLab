
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int head, disk;
vector<int> req;

void result(vector<int> order)
{
    int cur = head, total = 0;

    cout << "Seek Order: " << cur;
    for (int x : order)
    {
        total += abs(x - cur);
        cur = x;
        cout << " -> " << x;
    }
    cout << "\nTotal Seek Time = " << total << "\n";
}

// FCFS
void fcfs()
{
    result(req);
}

// SSTF
void sstf()
{
    vector<int> r = req;
    vector<int> order;
    int cur = head;

    while (!r.empty())
    {
        int pos = 0;
        for (int i = 1; i < r.size(); i++)
            if (abs(r[i] - cur) < abs(r[pos] - cur))
                pos = i;

        cur = r[pos];
        order.push_back(cur);
        r.erase(r.begin() + pos);
    }
    result(order);
}

// SCAN (move right first)
void scan()
{
    vector<int> r = req;
    vector<int> order;
    r.push_back(disk - 1);
    sort(r.begin(), r.end());

    for (int x : r)
        if (x >= head)
            order.push_back(x);

    for (int i = r.size() - 1; i >= 0; i--)
        if (r[i] < head)
            order.push_back(r[i]);

    result(order);
}

// C-SCAN (move right first)
void cscan()
{
    vector<int> r = req;
    vector<int> order;
    r.push_back(disk - 1);
    r.push_back(0);
    sort(r.begin(), r.end());

    for (int x : r)
        if (x >= head)
            order.push_back(x);

    for (int x : r)
        if (x < head)
            order.push_back(x);

    result(order);
}

int main()
{
    int n, choice;

    cout << "Enter number of requests: ";
    cin >> n;

    cout << "Enter disk size: ";
    cin >> disk;

    cout << "Enter head position: ";
    cin >> head;

    cout << "Enter requests: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        req.push_back(x);
    }

    do
    {
        cout << "\n1.FCFS  2.SSTF  3.SCAN  4.C-SCAN\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sstf();
            break;
        case 3:
            scan();
            break;
        case 4:
            cscan();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 5);
}