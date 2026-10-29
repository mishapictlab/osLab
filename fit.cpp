
#include <iostream>
#include <vector>
using namespace std;

vector<int> b, p;

// First Fit
void firstFit()
{
    vector<int> block = b;

    for (int i = 0; i < p.size(); i++)
    {
        int pos = -1;

        for (int j = 0; j < block.size(); j++)
        {
            if (block[j] >= p[i])
            {
                pos = j;
                break;
            }
        }

        if (pos == -1)
            cout << "P" << i + 1 << " -> Not Allocated\n";
        else
        {
            block[pos] -= p[i];
            cout << "P" << i + 1 << " -> B" << pos + 1 << "\n";
        }
    }
}

// Best Fit
void bestFit()
{
    vector<int> block = b;

    for (int i = 0; i < p.size(); i++)
    {
        int pos = -1;

        for (int j = 0; j < block.size(); j++)
        {
            if (block[j] >= p[i] && (pos == -1 || block[j] < block[pos]))
                pos = j;        //no break
        }

        if (pos == -1)
            cout << "P" << i + 1 << " -> Not Allocated\n";
        else
        {
            block[pos] -= p[i];
            cout << "P" << i + 1 << " -> B" << pos + 1 << "\n";
        }
    }
}

// Worst Fit
void worstFit()
{
    vector<int> block = b;

    for (int i = 0; i < p.size(); i++)
    {
        int pos = -1;

        for (int j = 0; j < block.size(); j++)
        {
            if (block[j] >= p[i] && (pos == -1 || block[j] > block[pos]))
                pos = j; // NO BREAK
        }

        if (pos == -1)
            cout << "P" << i + 1 << " -> Not Allocated\n";
        else
        {
            block[pos] -= p[i];
            cout << "P" << i + 1 << " -> B" << pos + 1 << "\n";
        }
    }
}

int main()
{
    int n, x, choice;

    cout << "Enter number of blocks: ";
    cin >> n;
    cout << "Enter block sizes: ";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        b.push_back(x);
    }

    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter process sizes: ";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        p.push_back(x);
    }

    do
    {
        cout << "\n1.First Fit  2.Best Fit  3.Worst Fit  4.Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            firstFit();
            break;
        case 2:
            bestFit();
            break;
        case 3:
            worstFit();
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice\n";
        }
    } while (choice != 4);

    return 0;
}