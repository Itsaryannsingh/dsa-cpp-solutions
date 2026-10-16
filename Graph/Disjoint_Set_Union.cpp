#include <iostream>
#include <vector>

using namespace std;

class DisjointSet
{
private:
    vector<int> parent;
    vector<int> size;

public:
    DisjointSet(int n)
    {
        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    // Find the representative of a set
    int findParent(int node)
    {
        if (parent[node] == node)
        {
            return node;
        }

        // Path Compression
        return parent[node] = findParent(parent[node]);
    }

    // Merge two sets
    void unite(int u, int v)
    {
        int parentU = findParent(u);
        int parentV = findParent(v);

        if (parentU == parentV)
        {
            cout << "Elements are already connected.\n";
            return;
        }

        // Union by Size
        if (size[parentU] < size[parentV])
        {
            parent[parentU] = parentV;
            size[parentV] += size[parentU];
        }
        else
        {
            parent[parentV] = parentU;
            size[parentU] += size[parentV];
        }

        cout << "Groups merged successfully.\n";
    }

    // Check whether two elements belong to the same set
    bool connected(int u, int v)
    {
        return findParent(u) == findParent(v);
    }
};

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Number of elements must be positive.\n";
        return 0;
    }

    DisjointSet ds(n);

    int choice;

    do
    {
        cout << "\n--- Disjoint Set Union ---\n";
        cout << "1. Union two elements\n";
        cout << "2. Find representative\n";
        cout << "3. Check connectivity\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int u, v;

        switch (choice)
        {
            case 1:
                cout << "Enter two elements: ";
                cin >> u >> v;

                if (u < 0 || u >= n || v < 0 || v >= n)
                {
                    cout << "Invalid element.\n";
                    break;
                }

                ds.unite(u, v);
                break;

            case 2:
                cout << "Enter element: ";
                cin >> u;

                if (u < 0 || u >= n)
                {
                    cout << "Invalid element.\n";
                    break;
                }

                cout << "Representative: "
                     << ds.findParent(u) << endl;
                break;

            case 3:
                cout << "Enter two elements: ";
                cin >> u >> v;

                if (u < 0 || u >= n || v < 0 || v >= n)
                {
                    cout << "Invalid element.\n";
                    break;
                }

                if (ds.connected(u, v))
                {
                    cout << "They belong to the same group.\n";
                }
                else
                {
                    cout << "They belong to different groups.\n";
                }

                break;

            case 4:
                cout << "Program terminated.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
