#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

vector<vector<int>>edge;
vector<int>dist;
vector<int>parent;
vector<int>path;
vector<int>wait;
map<string,int>mp;

bool  Bellmen(int n,int E)
{
   for(int i=0;i<n-1;i++)
   {
    for(int j=0;j<2*E;j++)
    {
       int u=edge[j][0];
       int v=edge[j][1];
       int w=edge[j][2];
       //cout<<u<<":"<<v<<":"<<w<<endl;
       if(dist[u]!=INT32_MAX && (dist[u]+w)<dist[v])
       {
         dist[v]=dist[u]+w;
         parent[v]=u;
       }      
    }
   }

    int cycle=1;
     for(int j=0;j<E;j++)
      {
       int u=edge[j][0];
       int v=edge[j][1];
       int w=edge[j][2];
      
       if(dist[u]!=INT32_MAX && (dist[u]+w)<dist[v])
       {
         cycle=0;
       }      
      }
    if(cycle)
    {
      return true;
    }
    else{
     return false;
    }
 }

 void findPath(int d,int s)
 { 
   path.push_back(d);
   if(parent[d]==s)
   {
      path.push_back(s);
      return;
   }
   else{
       findPath(parent[d],s);
   }
 }


 void write(ofstream &fout,int s,int d,int n,int m)
 {
  fout<<"Bellman Ford Algorithm:"<<endl;
    //cout<<Bellmen(n,m,d)<<endl;

  if(Bellmen(n,m))
  {

  fout<<dist[d]<<endl; 
  findPath(d,s);

  reverse(path.begin(),path.end());

  for(int i=0;i<path.size();i++)
  {
    //cout<<path[i];
    for(auto &it:mp)
    {
      if(it.second==path[i])
      {
          fout<<it.first;
      }
    }  
    if(i!=path.size()-1)
    {
        //cout<<"->";
        fout<<"->";
    }
  }
 // cout<<endl;
  fout<<endl;
  }

  else{
    fout<<"Negative cycle detected!"<<endl;
  }
 }

int main()
{
    int n,m;
    //cin>>n>>m;
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    fout.clear();
    fin>>n>>m;
    
    dist.assign(m,INT32_MAX);
    parent.assign(m,-1);
    wait.assign(n,-1);

    for(int i=0;i<n;i++)
    {
      string a;
      int l;
      fin>>a>>l;
      wait[i]=l;
      mp[a]=i;
    }

   
    for(int i=0;i<m;i++)
    {
      vector<int>arr;
      int a,b,c;
      string a1,a2;
      int t;
      //cin>>a>>b>>c;
      //fin>>a>>b>>c;
      fin>>a1>>a2>>t;
      a=mp[a1];
      b=mp[a2];
      c=t+wait[a];
      arr={a,b,c};
      edge.push_back(arr);
      c=t+wait[b];
      arr={b,a,c};
      edge.push_back(arr);

    }
    int s,d;
    string w,x;
    fin>>w>>x;
     s=mp[w];
     d=mp[x];
    dist[s]=0;
    write(fout,s,d,n,m);

    

  //cout<<dist[d]<<endl;
  fout.close();
  }