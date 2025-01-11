#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<queue>

using namespace std;

unordered_map<int,vector<pair<int,int>> >adj;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>> > Queue;
vector<int>parent;
vector<bool>visited;
vector<int>value;

void makeEdge(int a,int b,int w)
{
    adj[a].push_back({b,w});
    adj[b].push_back({a,w});
}

void PrimAlgo(int n,int s)
{
  value.assign(n,INT32_MAX);
  parent.assign(n,-1);
  visited.assign(n,false);
  Queue.push({0,s});
  value[s]=0;
  int sum=0;
  //parent[s]=-1;
  while(Queue.size())
  {
     int p,weight;
     p=Queue.top().second;
    // weight=Queue.top().first;
    // sum+=weight;

    visited[p]=true;
    Queue.pop();
    for(auto z:adj[p])
    {
        int q=z.first;
        int wt=z.second;
        if(visited[q]==false && wt<value[q])
        {
            value[q]=wt;
            parent[q]=p;
            Queue.push({wt,q});
        }
    }
    
  }
 // return sum;
}

void write(int n,int r,ofstream &fout)
{   
    int sum=0;
    for(int i=1;i<n;i++)
    {
        //fout<<parent[i]<<" "<<i<<endl;
        sum+=value[i];
    }
    fout<<"Total weight: "<<sum<<endl;
    fout<<"Root Node: "<<r<<endl;
    for(int i=1;i<n;i++)
    {
        fout<<parent[i]<<" "<<i<<endl;
    }
    
}

int main()
{
    /*int n,e;
    cin>>n>>e;
    for(int i=0;i<e;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        makeEdge(u,v,w);
    }
    PrimAlgo(n,0);
    print(n);*/
    ifstream fin("input.txt");
    ofstream fout("prim.txt");
    int n,m;
    fin>>n>>m;
    //cout<<n<<" "<<m<<endl;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        fin>>u>>v>>w;
        makeEdge(u,v,w);
    }
    PrimAlgo(n,0);
    //print(n);
    write(n,0,fout);
    fout.close();
}