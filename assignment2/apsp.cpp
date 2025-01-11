    #include<iostream>
    #include<vector>
    #include<fstream>
    #include<unordered_map>
    #include<queue>
    #include<algorithm>
    using namespace std;

    unordered_map<int,vector<pair<int,int>> >adj;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>> >Queue;
    vector<int> parent;
    vector<int>dist;
    vector<int>path;
    vector<vector<int>>mat;


    void makeEdge(int u,int v,int w)
    {
        adj[u].push_back({v,w});
    }

    void dijkstra()
    {

        while(Queue.size())
        {
            int u=Queue.top().second;
            Queue.pop();
            for(auto z:adj[u])
            {
                int v=z.first;
                int sd=z.second;
                if(dist[u]+sd<dist[v])
                {
                    parent[v]=u;
                    dist[v]=dist[u]+sd;
                    //cout<<dist[v]<<endl;
                    Queue.push({dist[v],v});
                }

        }

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

    /*void write(ofstream &fout,int s,int d)
    {
    fout<<"Dijsktra Algorithm:"<<endl;
        //cout<<Bellmen(n,m,d)<<endl;

    dijkstra();

    fout<<dist[d]<<endl; 
    findPath(d,s);

    reverse(path.begin(),path.end());

    for(int i=0;i<path.size();i++)
    {
        //cout<<path[i];
        fout<<path[i];
        if(i!=path.size()-1)
        {
            //cout<<"->";
            fout<<"->";
        }
    }
    // cout<<endl;
    fout<<endl;
    }*/


    int main()
    {
        int n,m,s,d;
        ifstream fin("input.txt");
        //ofstream fout("output1.txt",ios::app);
        fin>>n>>m;
        for(int i=0;i<m;i++)
        {
            int a,b,c;
            fin>>a>>b>>c;
            //cout<<a<<b<<c<<endl;
            makeEdge(a-1,b-1,abs(c));
        }
        //fin>>s>>d;

        for(int i=0;i<n;i++)
        {
        dist.assign(n,INT16_MAX);
        parent.assign(n,-1);
        Queue.push({0,i});
        dist[i]=0;
        dijkstra();
        //cout<<"HEl"<<endl;
        mat.push_back(dist);
        }


        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {   
                if(mat[i][j]==INT16_MAX)
                cout<<"INF ";
                else
                cout<<mat[i][j]<<" ";
            }
            cout<<endl;
        }
        
        //write(fout,s,d);
    // fout.close();
    }
