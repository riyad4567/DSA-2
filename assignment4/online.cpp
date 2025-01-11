#include <bits\stdc++.h>
#include <map>
#include <unordered_map>
using namespace std;

vector<vector<int>> cap;
// unordered_map<pair<int,int>,vector<int>>cap;
vector<vector<int>> resCap;
vector<vector<int>> augmentedPath;
map<int, int> parent;
vector<bool> visited;
vector<vector<int>> info;
vector<vector<int>> mat;
map<int, int> mp;

map<int, string> revMp;
map<pair<int, int>, int> pi;
map<int, pair<int, int>> ip;

bool bfs(int s, int d, int n)
{
  visited.assign(n, false);
  queue<int> Queue;
  //cout<<"Helow"<<endl;
  Queue.push(s);
  visited[s] = true;
  parent[s] = -1;
  bool found = false;
  while (!Queue.empty())
  {

    int u = Queue.front();
    Queue.pop();

    for (int v = 0; v < n; v++)
    {
      if (!visited[v] && resCap[u][v] > 0)
      {
        // parent[v]=u;
        // cout<<v<<endl;
        parent[v] = u;
        if (v == d)
        {
          return true;
        }
        Queue.push(v);
        visited[v] = true;
      }
    }
  }
  return found;
}

int maxFlow(int src, int snk, int n)
{
  //cout<<"BY"<<endl;
  resCap.assign(n, vector<int>(n));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      resCap[i][j] = mat[i][j];
    }
  }
  //cout<<"BY"<<endl;
  // map<int,int>parent;
  int maxflow = 0;
  while (bfs(src, snk, n))
  {
    int flow = INT16_MAX;
    int v = snk;
    vector<int> path;
    while (v != src)
    {
      path.push_back(v);
      int u = parent[v];
      // cout<<u<<endl;
      if (resCap[u][v] < flow)
      {
        flow = resCap[u][v];
      }
      v = u;
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    augmentedPath.push_back(path);
    //cout<<flow<<endl;
    maxflow += flow;
    v = snk;
     //cout<<maxflow<<endl;
    while (v != src)
    {
      int u = parent[v];
      resCap[u][v] -= flow;
      resCap[v][u] += flow;
      v = u;
    }
  }
  return maxflow;
}

/*int makeCapacity(int n, int node, int src, int sink, int index)
{
  int k = 0, sum = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      pi[{i, j}] = n + (k);
      ip[n + k] = {i, j};
      k++;
    }
  }
  cap.assign(node, vector<int>(node));
  // cout << src << " " << sink << endl;
  for (int i = 0; i < node; i++)
  {
    for (int j = 0; j < node; j++)
    {
      cap[i][j] = 0;
    }
  }
  for (int i = n; i < node; i++)
  {
    int x = ip[i].first;
    int y = ip[i].second;
    if (!(x == index || y == index))
    {
      if (mat[x][y] > 0)
      {
        cap[src][i] = mat[x][y];
        sum += cap[src][i];
        cap[i][x] = INT16_MAX;
        cap[i][y] = INT16_MAX;
      }
    }
  }

  return sum;
}*/

int main()
{
    ifstream fin("input1.txt");
    ofstream fout("output1.txt");
    int n,m,a;
    fin>>n>>m>>a;
    //cout<<n<<m<<a<<endl;
    int src=0;
    int sink=m+n+1;
    int num=m+n+2;
    mat.assign(num,vector<int>(num));
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {  
            mat[i][j]=0;
        }
    }
    for(int i=0;i<a;i++)
    {  
        int b;
        fin>>b;
        int k=mp[b]++;
        //cout<<k<<endl;
        mat[src][b]=k+1;
    }
    //cout<<"B"<<endl;
    /*for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    int f;
    for(int i=1;i<=n;i++)
    {
    fin>>f;
    cout<<"f"<<f<<endl;
    map<int, int> mp1;
    for(int j=1;j<=f;j++)
    {  
      // mat[j][m+i]=1;
       int c;
       //cout<<"H"<<endl;
       fin>>c;
       int k=mp1[c]++;
       cout<<k<<endl;
       mat[m+i][c]=k;
       mat[c][m+i]=0;
    }

    }
    for(int i=1;i<=m;i++)
    {
        mat[i][sink]=1;
    }
    for(int i=0;i<num;i++)
    {
        for(int j=0;j<num;j++)
        {
            cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }

    int p= maxFlow(src,sink,num);
    cout<<p<<endl;
    fout<<p<<endl;



}