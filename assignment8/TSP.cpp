#include <bits\stdc++.h>
using namespace std;

vector<vector<int>> edge;
vector<int> parent;
vector<int> height;

int findParent(int u)
{
    if (parent[u] == -1)
    {
        return u;
    }
    else
    {
        parent[u] = findParent(parent[u]);
        return parent[u];
    }
}
void makeUnion(int a, int b)
{
    int p, q;
    p = findParent(a);
    q = findParent(b);
    if (height[p] >= height[q])
    {
        parent[q] = p;
        height[p] += height[q];
    }
    else
    {
        parent[p] = q;
        height[q] += height[p];
    }
}
void DFS(int u, int p, vector<vector<int>> adj, vector<int> &store)
{
    store.push_back(u);
    for (int v : adj[u])
    {
        if (v != p)
        {
            DFS(v, u, adj, store);
        }
    }
}


 void Create_Random_Graph(int n, vector<vector<int>>&arr)
    {
        //int random = 50 + (rand() % 151);
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                int random =50+(rand() % 151);
                arr[i][j]=random;
                arr[j][i]=random;
               // cout<<random<<" ";

            }
            //cout<<endl;
        }
        for(int k=0;k<n;k++)
        {
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(arr[i][j]>arr[i][k]+arr[k][j])
                    {
                        arr[i][j]=arr[i][k]+arr[k][j];
                    }
                }
            }
        }
    }

class Graph
{
public:
    int n;
    vector<vector<int>> mat;
    vector<vector<int>> DP;
    vector<vector<int>> adj;
    Graph(int sz, vector<vector<int>> arr)
    {
        n = sz;
        mat.resize(n, vector<int>(n, -1));
        adj.assign(n, vector<int>());
        DP.resize(1 << n, vector<int>(n, -1));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                mat[i][j] = arr[i][j];
            }
        }
    }
    int Exact_TSP(int mask, int pos, int visitAll)
    {
        int ans = INT_MAX;
        if (DP[mask][pos] != -1)
        {
            return DP[mask][pos];
        }
        if (mask == visitAll)
        {
            return mat[pos][0];
        }
        for (int i = 0; i < n; i++)
        {
            if ((mask & (1 << i)) == 0)
            {
                int newans = mat[pos][i] + Exact_TSP(mask | (1 << i), i, visitAll);
                ans = min(ans, newans);
            }
        }
        return DP[mask][pos] = ans;
    }

    void Metric_Approximation_TSP(vector<int> &store)
    {
        vector<vector<int>> getEdge;
        sort(edge.begin(), edge.end());
        for (auto a : edge)
        {
            int u, v, wt, i, j, l;
            wt = a[0];
            i = a[1];
            j = a[2];
            // cout<<wt<<" "<<i<<" "<<j<<endl;
            u = findParent(i);
            v = findParent(j);
            // cout<<u<<"   "<<v<<endl;
            if (u != v)
            {
                // sum += wt;
                //  cout<<i<<" "<<j<<endl;
                getEdge.push_back({i, j});
                // s += to_string(i) + " " + to_string(j) + '\n';
                makeUnion(i, j);
                // for(int i=0;i<n;i++)
                // cout<<parent[i]<<" ";

                // cout<<endl;
            }
        }
        // cout << "Total weight: " << sum << endl;
        for (int i = 0; i < getEdge.size(); i++)
        {
            int p, q;
            p = getEdge[i][0];
            q = getEdge[i][1];
            adj[p].push_back(q);
            adj[q].push_back(p);
            // cout<<p<<" "<<q;
           // cout << endl;
        }

        DFS(0, -1, adj, store);
        store.push_back(0);
    }
    int Calculate_Tour_Length(vector<int> store)
    {
        // for (int k : store)
        // {
        //     cout << k << " ";
        // }
       // cout << endl;

        int len = store.size();
        int w = 0;
        for (int i = 0; i < len - 1; i++)
        {
            // cout<<mat[store[i]][store[i + 1]]<<endl;
            w += mat[store[i]][store[i + 1]];
        }
        return w;
    }
   
};

int main()
{
    int n = 20, m, sum = 0, x;
    cout<<"Enter a value of X: ";
    cin >> x;
    int A[x], B[x];
    for (int i = 0; i < x; i++)
    {

        //vector<vector<int>> arr{{0, 10, 15, 60}, {10, 0, 25, 25}, {15, 25, 0, 30}, {60, 25, 30, 0}};
        vector<vector<int>> arr(n,vector<int>(n, 0));
        //srand(time(0));
        Create_Random_Graph(n,arr);
        Graph obj(n, arr);
        int visitAll = (1 << n) - 1;
        // for(int i=0;i<n;i++)
        // {
        //     for(int j=0;j<n;j++)
        //     {
        //         cout<<arr[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        //cout << "Minimum cost Travelled -> " << obj.Exact_TSP(1, 0, visitAll)<<endl;
        A[i] = obj.Exact_TSP(1, 0, visitAll);

        // int n,m,sum=0;
        // string s;
        // cin>>n>>m;


        // make set

        height.assign(n, 1);
        parent.assign(n, -1);
        // m = n * (n - 1) / 2;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    vector<int> arr1;
                    int u = i, v = j, w = arr[i][j];
                    // cin>>u>>v>>w;
                    // fin>>u>>v>>w;

                    arr1 = {w, u, v};
                    edge.push_back(arr1);
                }
            }
        }

        // cout<<getEdge.size();
        vector<int> store;

        obj.Metric_Approximation_TSP(store);
        int w = obj.Calculate_Tour_Length(store);

        B[i] = w;
        //cout << w << " M  " << endl;
    }
    for(int i=0;i<x;i++)
    {
        cout<<"("<<i+1<<", "<<B[i]/(1.0*A[i])<<")"<<endl;
    }
}