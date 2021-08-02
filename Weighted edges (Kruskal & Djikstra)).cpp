#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct node
{
    int id;
    int data;
};

struct edge
{
    int id1, id2, dist;
};

void merge(vector <int>& v1, vector <int>& v2)
{
    bool flag = true;
    for (int i = 0; i < v2.size(); i++)
    {
        flag = true;
        for (int j = 0; j < v1.size(); j++)
        {
            if (v1[j] = v2[i]) flag = false;
        }
        if (!flag) v1.push_back(v2[i]);
    }

    sort(v1.begin(), v1.end());
    v2 = {};
    return;
}

void display_ve(vector <edge> g)
{
    int nc = g.size();
    for (int i = 0; i < nc; i++)
        cout << g[i].id1 << ' ' << g[i].id2 << ' ' << g[i].dist << endl;
    return;
}

void display_vvi(vector <vector <int>> g)
{
    for (int i = 0; i < g.size(); i++)
    {
        for (int j = 0; j < g[i].size(); j++)
            cout << g[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
    return;
}

void swap_edge(edge& e1, edge& e2)
{
    edge temp = e1;
    e1 = e2;
    e2 = temp;
    return;
}

void sortedge_dist(vector <edge>* e)
{
    int n = e->size();
    for (int i = 0; i < n; i++)
        for (int j = 1; j < n - i; j++)
            if ((*e)[j].dist < (*e)[j - 1].dist)
                swap((*e)[j - 1], (*e)[j]);
    return;
}

class graph
{
    vector <node> n;
    vector <vector<int>> g;
    int nc, ec;
    vector <edge>* ch;                              //pointer of a vector consisting of edges.
public:
    graph()
    {
        ch = NULL;
        nc = 0;
        ec = 0;
        n = {};
        g = {};
    }

    void display()
    {
        for (int i = 0; i < nc; i++)
        {
            for (int j = 0; j < nc; j++)
                cout << g[i][j] << " ";
            cout << endl;
        }
        return;
    }

    vector <vector<int>> get_g()
    {
        return g;
    }

    void add_node()
    {
        node temp;
        temp.id = ++nc;
        cin>>temp.data;
        n.push_back(temp);
        for (int i = 0; i < nc - 1; i++) g[i].push_back(0);

        vector <int> vec;
        for (int i = 0; i < nc; i++) vec.push_back(0);
        g.push_back(vec);
    }

    void def_graph(vector<edge>* ch1 = NULL)
    {
        if (ch1 == NULL)
        {
            if (ch == NULL)
            {
                cout << "ERROR... Edge set not provided...\n";
                return;
            }
        }
        else ch = ch1;

        ec = ch->size();

        for (int i = 0; i < ec; i++) 
            g[(*ch)[i].id1 - 1][(*ch)[i].id2 - 1] = g[(*ch)[i].id2 - 1][(*ch)[i].id1 - 1] = (*ch)[i].dist;

        return;
    }

    vector <edge> kruskal ()
    {
        sortedge_dist(ch);
        vector <edge> res;
        vector<vector<int>> trees;
        vector <int> vec;
        int temp;
        int flag = 0;

        vector<bool> check;
        for (int i = 0; i < nc; i++) check.push_back(false);

        vec.push_back((*ch)[0].id1);
        vec.push_back((*ch)[0].id2);
        res.push_back((*ch)[0]);
        check[(*ch)[0].id1] = check[(*ch)[0].id2] = true;
        trees.push_back(vec);
        vec = {};

        for (int i = 0; i < ec; i++)
        {
            flag = 0;
            for (int j = 0; j < trees.size(); j++)
            {
                if (flag == 0)
                {
                    for (int k = 0; k < trees[j].size(); k++)
                        if (trees[j][k] == (*ch)[i].id1 || trees[j][k] == (*ch)[i].id2) flag++;
                    
                    if (flag == 1) temp = j;
                    if (flag == 2) flag=-1;
                }

                else if (flag == 1)
                {
                    for (int k=0; k<trees[j].size(); k++)
                        if (trees[j][k] == (*ch)[i].id1 || trees[j][k] == (*ch)[i].id2)
                        {
                            flag++;
                            res.push_back((*ch)[i]);
                        }

                    if (flag == 2)
                    {
                        merge(trees[temp], trees[j]);
                        flag = -1;
                    }
                }

                if (flag == -1) break;
            }

            if (flag == 0)
            {
                res.push_back((*ch)[i]);
                vec.push_back((*ch)[i].id1);
                vec.push_back((*ch)[i].id2);
                trees.push_back(vec);
                vec = {};
            }

            else if (flag == 1)
            {
                res.push_back((*ch)[i]);
                bool flag1 = false;

                for (int j = 0; j < trees[temp].size(); j++) if (trees[temp][j] == (*ch)[i].id1) flag1 = true;

                if (flag1) trees[temp].push_back((*ch)[i].id2);
                else trees[temp].push_back((*ch)[i].id1);
            }
        }
        return(res);
    }

    /*
    vector <vector <int>> dijkstra(int id1, int id2)
    {
        vector <bool> visited;
        vector <vector <int>> n1;
        for (int i = 0; i < nc; i++) 
        {
            n1.push_back({ -1 }); visited.push_back(false);
        }
        n1[id1-1][0] = 0;
        visited[id1-1] = true;

        while (n1[id2-1][0] == -1)
        {
            //cout << "fyn";
            for (int i = 0; i < nc; i++) if (n1[i][0] > -1) n1[i][0]++;                    //Can be modified eg what if my weights are 1000 2300 4050 ...

            //display_vvi(n1);

            for (int i = 1; i < nc+1; i++)
            {
                if (visited[i] && n1[i-1][0] > -1)                                            //Both are same ryt... check it... U have implemented visted in the vecvecint itself
                {
                    for (int j = 1; j < nc+1; j++)
                    {
                        if (j == i) continue;
                        if (n1[i-1][0] >= g[i-1][j-1] && n1[j-1][0] <= 0  )
                        {
                            visited[j-1] = true;
                            n1[j-1][0] = 0;
                            n1[j-1].push_back(i); 
                        }
                    }
                }
            }
        }
        return(n1);
    }*/

    vector <vector <int>> dijkstra(int id1, int id2)
    {
        vector <vector<int>> res;
        vector <int> temp;

        for (int i = 0; i < nc; i++) res.push_back({ -1 });
        res[id1 - 1][0] = 0;

        while (res[id2 - 1][0] == -1)
        {
            //cout << id1 << ' ' << nc;
            for (int i = 0; i < nc; i++) if (res[i][0] != -1) res[i][0]++;
            //display_vvi(res); cout << endl;
            for (int i = 0; i < nc; i++)
            {
                if (res[i][0] == -1) continue;
                for (int j = 0; j < nc; j++)
                    if (res[j][0]<=0 && res[i][0] == g[i][j])
                    {
                        res[j][0] = 0;
                        res[j].push_back(i+1);
                    }
            }
        }
        return(res);
    }
}; 

int main()
{
    graph g1;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) g1.add_node();

    vector <edge> t;
    edge temp;
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        for (cin >> temp.id1; temp.id1 <= 0 || temp.id1 > n; cin >> temp.id1) cout << "incorrect id1 value... re-enter...";
        for (cin >> temp.id2; temp.id2 <= 0 || temp.id2 > n; cin >> temp.id2) cout << "incorrect id2 value... re-enter...";
        for (cin >> temp.dist; temp.dist < 0; cin >> temp.dist) cout << "incorrect dist value... re-enter...";
        //cin >> temp.id1 >> temp.id2 >> temp.dist;
        t.push_back(temp);
    }

    g1.def_graph(&t);
    g1.display();

    vector <edge> krus = g1.kruskal();
    display_ve(krus);

    display_vvi(g1.dijkstra(5, 2));
    //display_vvi(g1.dijkstra(5, 3)); cout << endl;
    //display_vvi(g1.dijkstra(5, 1));

    return(0);
}

/*
* 
* input:
* number of nodes
* node ids 
* 
* number of edges
* define edges (id1, id2, dist)


5
 1 2 3 4 5
 7
 1 2 3
 1 4 7
 1 5 8
 2 3 1
 2 4 4
 3 4 2
 4 5 3



*/
