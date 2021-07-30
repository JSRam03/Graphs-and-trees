
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node
{
    int id;
    int data;
};

class graph
{
    vector <vector<int>> g;
    vector <node> n;
    int count;
public:

    vector <vector<int>> get_g()
    {
        return(g);
    }

    graph()
    {
        count = 0;
    }

    void display()
    {
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
                cout << g[i][j] << ' ';
            cout << endl;
        }

        cout << endl;

        /*for (int i = 0; i < count; i++)
            cout << n[i].id << ' ' << n[i].data << endl;*/
        
        return;
    }

    void add_node()
    {
        vector <int> connected_id = {};
        vector <int> tempvec;
        int y;
        node temp;
        temp.id = count++;
        cin >> temp.data;
        for (cin >> y; y >= 0 && y<count; cin >> y) connected_id.push_back(y);
        
        n.push_back(temp);
        for (int i = 0; i < count-1; i++) g[i].push_back(0);
        for (int i = 0; i < count; i++) tempvec.push_back(0);
        g.push_back(tempvec);  

        for (int i = 0; i < connected_id.size(); i++)
            g[count - 1][connected_id[i]-1] = g[connected_id[i]-1][count - 1] = 1;

        g[count - 1][count - 1] += connected_id.size();

        for (int i = 0; i < connected_id.size(); i++) g[connected_id[i]-1][connected_id[i]-1]++;

        return;
    }
};

bool is_connected(vector <vector<int>> g)
{
    vector <bool> check;
    for (int i = 0; i < g.size(); i++) check.push_back(false);
    queue <int> order;
    order.push(0);
    check[0] = true;
    while (order.size() > 0)
    {
        int t = order.front();
        order.pop();
        for (int i = 0; i < g.size(); i++)
        {
            if (i == t) continue;
            if (g[i][t] != 0 ) order.push(i);
        }
        check[t] = true;
        //for (; !check[order.front()] ; order.pop());
        while (check[order.front()])
        {
            //cout<<order.front()<<endl;
            order.pop();
            if (order.size() == 0) break;
        }
    }
    for (int i = 0; i < check.size(); i++) if (!check[i]) return (false);
    return(true);
}

int main()
{
    int n;
    cin >> n;
    graph g1;
    for (int i = 0; i < n; i++) g1.add_node();

    g1.display();

    cout << endl;
    if (is_connected(g1.get_g())) cout << "Connected\n";
    else cout << "Not Connected\n";

    return(0);
}

/*
 
 4
 1 -1
 2 1 -1
 3 1 -1
 4 1 2 -1

*/