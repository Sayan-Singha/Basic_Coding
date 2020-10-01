#include <iostream>
using namespace std;

char par[128];

char find(char c)
{
    while (par[(int)c] != -1)
        c = par[(int)c];
    return c;
}

int main()
{
    int n, e;
    for (int i = 0;i < 128;i++)
        par[i] = -1;
    char u, v;
    int option = 1;
    while (option != 3) {
        cout << "1. ENTER THE EDGE: \n";
        cout << "2. FIND PARENT OF NODE: \n";
        cout << "3. EXIT \n";
        cout <<"4. ENTER YOUR OPTION: ";
        cin >> option;
        if (option == 1) {
            cin >> u >> v;
            if (find(u) == find(v))
                cout << "cycle formed in the graph\n";
            else
                par[find(u)] = find(v);
        }
        else if (option == 2) {
            char c;
            cin >> c;
            cout << "PARENT OF NODE IS: " << find(c) << "\n";
        }
    }
 }

