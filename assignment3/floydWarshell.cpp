   #include<bits\stdc++.h>

   using namespace std;
   //vector<vector<int>>matrix;

   void Floyd(int n,vector<vector<int>>&matrix)
   { 
   // cout<<matrix.size()<<endl;
   for(int i=1;i<=n;i++)
   {
      for(int j=1;j<=n;j++)
      {
         for(int k=1;k<=n;k++)
         {
            matrix[j][k]=min((matrix[j][i]+matrix[i][k]),matrix[j][k]);
         }
      }
   }
   }

   int main()
   {
      int n,m;
      ifstream fin("input.txt");
      ofstream fout("floyd.txt");
      fin>>n>>m;
      vector<vector<int>>matrix(n+1,vector<int>(n+1,INT16_MAX));
      for(int i=0;i<m;i++)
      { 
      int a,b,c;
      fin>>a>>b>>c;
      matrix[a][b]=c;
      matrix[a][a]=0;
      matrix[b][b]=0;
      }
      Floyd(n,matrix);
      fout<<"Floyd-Warshell Algorithm: "<<endl;
      for(int i=1;i<n+1;i++)
      {
         for(int j=1;j<n+1;j++)
         {  
            if(matrix[i][j]==INT16_MAX)
            {
            //cout<<"INF"<<" ";
            fout<<"INF"<<" ";
            }
            
            else
            {
            // cout<<matrix[i][j]<<" ";
               fout<<matrix[i][j]<<" ";
            }
            
         }
         //cout<<endl;
         fout<<endl;
      }
   }