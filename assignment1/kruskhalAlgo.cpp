    #include<iostream>
    #include<vector>
    #include<algorithm>
    #include<fstream>

    using namespace std;

    vector<vector<int>>edge;
    vector<int>parent;
    vector<int>height;


    int findParent(int u)
    {
    if(parent[u]==-1)
    {
        return u;
    }
    else{
            parent[u]=findParent(parent[u]);
            return parent[u];
    }
    }
    void makeUnion(int a,int b)
    {     
    int p,q;
    p=findParent(a);
    q=findParent(b);
    if(height[p]>=height[q])
    {
        parent[q]=p;
        height[p]+=height[q];
    }
    else{
        parent[p]=q;
        height[q]+=height[p];
    }

    }

    int main()
    {
    int n,m,sum=0;
    string s;
    //cin>>n>>m;

    ifstream fin("input.txt");
    ofstream fout("kruskal.txt");
    fin>>n>>m;

    //make set

    height.assign(n,1);
    parent.assign(n,-1);



    for(int i=0;i<m;i++)
    {
    vector<int> arr;
    int u,v,w;
    //cin>>u>>v>>w;
    fin>>u>>v>>w;

    arr={w,u,v};
    edge.push_back(arr);

    }

    sort(edge.begin(),edge.end());
    for(auto a:edge)
    {
    int u,v,wt,i,j,l;
    wt=a[0];
    i=a[1];
    j=a[2];
    //cout<<wt<<" "<<i<<" "<<j<<endl;
    u=findParent(i);
    v=findParent(j);
    //cout<<u<<"   "<<v<<endl;
    if(u!=v)
    { 
        sum+=wt;
        //cout<<i<<" "<<j<<endl;
        s+=to_string(i)+" "+to_string(j)+'\n';
        makeUnion(i,j);
        for(int i=0;i<n;i++)
        cout<<parent[i]<<" ";

        cout<<endl;
    }
    }
    // cout<<sum<<endl;
    fout<<"Total weight: "<<sum<<endl;
    fout<<s<<endl;
    fout.close();
    }