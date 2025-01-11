  #include<bits\stdc++.h>

  using namespace std;

  class Matrix{
      public:
      int size;
      vector<vector<int>>arr;
      Matrix(int x)
      {
        size=x;
        arr.resize(size+1,vector<int>(size+1,INT16_MAX));
        for(int i=0;i<=size;i++)
        {
          arr[i][i]=0;
        }
      }

      Matrix multiplication(Matrix L,Matrix W)
      {
        int s=L.size;
        Matrix R(s);
        for(int i=1;i<=s;i++)
        {
          for(int j=1;j<=s;j++)
          {
              for(int k=1;k<=s;k++)
              {
                R.arr[i][j]=min(R.arr[i][j],(L.arr[i][k]+W.arr[k][j]));
              }
          }
        }
        return R;
      }

      Matrix getMatrix(int n,Matrix W)
      {
        if(n==1)
        {
          return W;
        }
        Matrix temp=getMatrix(n/2,W);
        temp=multiplication(temp,temp);

        if(n%2==1)
        {
          temp=multiplication(temp,W);
        }
        return temp;

      }

      Matrix shortestPath(vector<vector<int>>adj,int n)
      {    
        // Matrix Wt(n);
          Matrix L(n);
        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=n;j++)
            {
            // Wt.arr[i][j]=adj[i][j];
              L.arr[i][j]=adj[i][j];
            }
        }
      // L=getMatrix(n,L);
       return L;
      }
  };



  int main()
  {
    int n,m;
    ifstream fin("input.txt");
    ofstream fout("matrix.txt");
    fout.clear();
    fin>>n>>m;
    vector<vector<int>>adj(n+1,vector<int>(n+1,INT16_MAX));
    for(int i=0;i<m;i++)
    { 
      int a,b,c;
      fin>>a>>b>>c;
      adj[a+1][b+1]=c;
      adj[a+1][a+1]=0;
      adj[b+1][b+1]=0;
    }

    Matrix temp(n),temp1(n);
    temp=temp.shortestPath(adj,n);
    temp=temp.getMatrix(n-1,temp);
    fout<<"Matrix Multiplication Method: "<<endl;
    for(int i=1;i<=n;i++)
    {
      for(int j=1;j<=n;j++)
      {
        if(temp.arr[i][j]==INT16_MAX)
          {
            //cout<<"INF"<<" ";
            fout<<"INF"<<" ";
          }
          
          else
          {
            // cout<<temp.arr[i][j]<<" ";
              fout<<temp.arr[i][j]<<" ";
          }
      }
      fout<<endl;
    }
     temp1=temp1.shortestPath(adj,n);
     temp1=temp1.getMatrix(n+8,temp1);
      if(temp.arr!=temp1.arr)
      {
        cout<<"YES"<<endl;
      }
      else{
        cout<<"NO"<<endl;
      }
      for(int i=1;i<=n;i++)
      {
        for(int j=1;j<=n;j++)
        {
            if(temp1.arr[i][j]==INT16_MAX)
          {
            //cout<<"INF"<<" ";
            fout<<"INF"<<" ";
          }
          
          else
          {
            // cout<<temp.arr[i][j]<<" ";
              fout<<temp1.arr[i][j]<<" ";
          }
        }
        fout<<endl;
      }

      
      //cout<<endl;
      fout<<endl;

  }