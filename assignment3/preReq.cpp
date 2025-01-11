#include<bits\stdc++.h>

   using namespace std;
   //vector<vector<int>>matrix;

   void Floyd(int n,vector<vector<int>>&matrix)
   { 
   // cout<<n<<endl;
   for(int i=0;i<=n;i++)
   {
      for(int j=0;j<=n;j++)
      {
         for(int k=0;k<=n;k++)
         {
            matrix[j][k]=min((matrix[j][i]+matrix[i][k]),matrix[j][k]);
         }
      }
   }
   }

    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries)
    {
        int n=numCourses;
        int len=queries.size();
        vector<vector<int>>matrix(n,vector<int>(n,1000));
        vector<bool>arr;
        for(int i=0;i<n;i++)
        {  
           int a=prerequisites[i][0];
           int b=prerequisites[i][1];
           matrix[a][b]=1;
           matrix[a][a]=0;
           matrix[b][b]=0;
        }
        Floyd(n,matrix);
        for(int i=0;i<len;i++)
        {
   
            int u=queries[i][0];
            int v=queries[i][1];
            if(matrix[u][v]!=1000)
            {
               arr.push_back(true);
            }
            else{
                arr.push_back(false);
            }

        }
        return arr; 
    }


   


