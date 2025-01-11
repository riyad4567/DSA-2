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
map<string, int> mp;
map<int, string> revMp;
map<pair<int, int>, int> pi;
map<int, pair<int, int>> ip;

bool bfs(int s, int d, int n)
{
  visited.assign(n, false);
  queue<int> Queue;
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
  resCap.assign(n, vector<int>(n));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      resCap[i][j] = cap[i][j];
    }
  }
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
    // cout<<maxflow<<endl;
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

int makeCapacity(int n, int node, int src, int sink, int index)
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
}

int main()
{
  ifstream fin("input.txt");
  ofstream fout("output.txt");

  /*cap={ { 0, 16, 13, 0, 0, 0 },{ 0, 0, 10, 12, 0, 0 },
        { 0, 4, 0, 0, 14, 0 }, { 0, 0, 9, 0, 0, 20 },
        { 0, 0, 0, 7, 0, 4 }, { 0, 0, 0, 0, 0, 0 } };
   cout<<maxFlow(0,5,6)<<endl;*/

  int n;
  fin >> n;
  info.assign(n, vector<int>(3));
  mat.assign(n, vector<int>(n));
  for (int i = 0; i < n; i++)
  {
    string s;
    int a, b, c;
    fin >> s >> a >> b >> c;
    mp[s] = i;
    revMp[i] = s;
    info[i][0] = a;
    info[i][1] = b;
    info[i][2] = c;
    for (int j = 0; j < n; j++)
    {
      int x;
      fin >> x;
      mat[i][j] = x;
    }
  }

  int node = n + n * (n - 1) / 2 + 2;
  int src = (n * (n - 1) / 2) + n;
  int sink = (n * (n - 1) / 2) + n + 1;
  // cout<<"Node: "<<node<<endl;
  // cap.assign(node,vector<pair<int,int>>(node));
  // visited.assign(node, false);
  int maxwin=0,store=0;
  for(int i=0;i<n;i++)
  {
    if(info[i][0]>maxwin)
    {
      maxwin=info[i][0];
      store=i;
    }
  }
  //cout<<maxwin<<endl;
  for (int i = 0; i < n; i++)
  { 
    int flag=1;
    int sum = makeCapacity(n, node, src, sink, i);
    for (int j = 0; j < n; j++)
    {
      if (i != j)
      {
        int p = info[i][0] + info[i][2] - info[j][0];
        if (p < 0)
        {
          //cout << revMp[i] << " is eliminated" << endl;
          fout << revMp[i] << " is eliminated" << endl;
          flag=0;
          break;
        }
        cap[j][sink] = p;
      }
    }

    //for Bonus part---------
    int count=0,play=0;
    vector<int>lis;
    int mx = maxFlow(src, sink, node);
    //cout << mx << "  " << sum << endl;
    if (mx < sum && flag==1)
    {
      //cout << revMp[i] << " is eliminated" << endl;
      fout << revMp[i] << " is eliminated" << endl;
      for(int a=0;a<n;a++)
      {
        if(bfs(src,a,node))
        {
          //count++;
          lis.push_back(a);
        }
      }
      fout<<"They can win at most "<<info[i][0]<<"+"<<info[i][2]<<"="<<info[i][0]+info[i][2]<<" games"<<endl;
      for(int d=0;d<lis.size();d++)
      {
        fout<<revMp[lis[d]];
        if(d!=lis.size()-1)
        {
          fout<<" and ";
        }
        count+=info[lis[d]][0];
      }
      fout<<" have won a total of "<<count<<" games"<<endl;
      fout<<"They play each other ";
      for(int u=0;u<lis.size();u++)
      {
        for(int v=u+1;v<lis.size();v++)
        {
          play+=mat[lis[u]][lis[v]];
        }
      }
      fout<<play<<" times"<<endl;
      fout<<"So on average, each of the teams wins "<<(play+count)<<"/"<<lis.size()<<"="<<(play+count)/(lis.size()*1.0)<<" games"<<endl;
      fout<<endl;
    }

    else if(flag==0)
    {
      fout<<"They can win at most "<<info[i][0]<<"+"<<info[i][2]<<"="<<info[i][0]+info[i][2]<<" games"<<endl;
      fout<<revMp[store]<<" have won a total of "<<info[store][0]<<" games"<<endl;
      fout<<"They play each other 0 times"<<endl;
      fout<<"So on average, each of the teams wins "<<maxwin<<"/"<<1<<"="<<maxwin<<" games"<<endl;
      fout<<endl;
    }

    /*for (int k = 0; k < node; k++)
    {
      for (int l = 0; l < node; l++)
      {
        cout << resCap[k][l] << " ";
      }
      cout << endl;
      
    }
    cout << endl;
    cout<<count<<endl;*/
  }
  

  /*for (int i = 0; i < augmentedPath.size(); i++)
  {
    for (int j = 0; j < augmentedPath[i].size(); j++)
    {
      cout << augmentedPath[i][j] << "->";
    }
    cout << endl;
  }*/
}