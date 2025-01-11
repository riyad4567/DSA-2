#include <bits/stdc++.h>

using namespace std;

int N2;

class HashTable
{
public:
    int size;
    int chainCount;
    int doubleCount;
    int customCount;
    int doubleCollision;
    int chainCollision;
    int customCollision;
    list<pair<string, int>> *table;
    vector<pair<string, int>> vec;
    // HashTable(int N)
    // {
    //     size = N;
    //     chainCount=0;
    //     doubleCount=0;
    //     customCount=0;
    //     table = new list<pair<string, int>>[size];
    // }
    HashTable(int N)
    {
        vec.resize(N);
        table = new list<pair<string, int>>[N];
        size = N;
        chainCount = 0;
        doubleCount = 0;
        customCount = 0;
        doubleCollision = 0;
        chainCollision = 0;
        customCollision = 0;
        for (int i = 0; i < N; i++)
        {
            // cout<<"IN"<<endl;
            vec[i].second = -1;
            table[i].push_back({"", -1});
        }
    }
    int Hash1(string key)
    {
        int len = key.size();
        long long int sum = 0;
        for (int i = 0; i < len; i++)
        {
            sum += (int(key[len - 1 - i]) - 96) * pow(37, i);
        }
        // cout<<sum%size<<endl;
        return (sum % size);
    }
    int Hash2(string key)
    {
        int len = key.size();
        long long int sum = 0;
        for (int i = 0; i < len; i++)
        {
            sum += (int(key[i]) - 96) * pow(29, i);
        }
        // cout<<sum<<endl;
        //  cout<<sum%size<<endl;
        return (sum % size);
    }
    int InsertChain(string key, int value, string choose)
    {
        chainCollision = 0;
        if (value > size)
        {
            return -1;
        }
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        for (auto i = table[index].begin(); i != table[index].end(); i++)
        {
            if ((*i).first == key)
            {
                return -2;
            }
        }
        for (auto x = table[index].begin(); x != table[index].end(); x++)
        {
            if ((*x).second != -1)
            {
                chainCollision++;
                table[index].push_back({key, value});
                return 0;
            }
            else
            {
                table[index].erase(x);
                table[index].push_back({key, value});
                return 0;
            }
        }
    }
    void DeleteChain(string key, string choose)
    {
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        // list<int>::iterator i;
        for (auto i = table[index].begin(); i != table[index].end(); i++)
        {
            if ((*i).first == key)
            {
                table[index].erase(i);
                break;
            }
        }
    }
    // void DisplayHash1()
    // {
    //     for (int i = 0; i < size; i++)
    //     {
    //         cout << "table[" << i << "]";
    //         for (auto x : table[i])
    //             cout << " --> " << x.first << " " << x.second;
    //         cout << endl;
    //     }
    // }
    int FindChain(string key, string choose)
    {
        chainCount = 0;
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        for (auto i = table[index].begin(); i != table[index].end(); i++)
        {

            if ((*i).first == key)
            {
                return (*i).second;
            }
            chainCount++;
        }
        return -1;
    }
    int AuxFunction(int index, int x)
    {
        int p = x * ((N2 - index % N2));
        return p;
    }
    int DoubleHash(string key, int x, string choose)
    {
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        return (index + AuxFunction(index, x)) % size;
    }
    int InsertDouble(string key, int value, string choose)
    {
        doubleCollision = 0;
        if (value > size)
        {
            return -1;
        }
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        for (int i = 1; i <= size; i++)
        {
            auto it = vec[index];
            if (it.first == key)
            {
                return -2;
            }
            if (it.second == -1)
            {
                vec[index].first = key;
                vec[index].second = value;
                return 0;
            }
            else
            {
                doubleCollision++;
                index = DoubleHash(key, i, choose);
            }
        }
    }
    void DeleteDouble(string key, string choose)
    {
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        for (int i = 1; i < size; i++)
        {
            auto it = vec[index];
            if (it.first == key)
            {
                vec[index].first = "";
                vec[index].second = -1;
                break;
            }
            else
            {
                index = DoubleHash(key, i, choose);
            }
        }
    }
    int FindDouble(string key, string choose)
    {
        doubleCount = 0;
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        for (int i = 1; i <=size; i++)
        {
            auto it = vec[index];
            if (it.second == -1)
            {
                return -1;
            }
            if (it.first == key)
            {
                return vec[index].second;
            }
            else
            {
                index = DoubleHash(key, i, choose);
                doubleCount++;
            }
        }
        return -1;
    }
    int InsertCustom(string key, int value, string choose)
    {
        customCollision = 0;
        if (value > size)
        {
            return -1;
        }
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        for (int i = 1; i <=size; i++)
        {
            auto it = vec[index];
            if (it.first == key)
            {
                return -2;
            }
            if (it.second == -1)
            {
                vec[index].first = key;
                vec[index].second = value;
                return 0;
            }
            else
            {
                index = customHash(key, i, choose);
                customCollision++;
            }
        }
    }
    void DeleteCustom(string key, string choose)
    {
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        for (int i = 1; i <=size; i++)
        {
            auto it = vec[index];
            if (it.first == key)
            {
                vec[index].first = "";
                vec[index].second = -1;
                break;
            }
            else
            {
                index = customHash(key, i, choose);
            }
        }
    }
    int FindCustom(string key, string choose)
    {
        customCount = 0;
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
       
        for (int i = 1; i <size; i++)
        {
            auto it = vec[index];
            if (it.second == -1)
            {   
                // cout<<"Hello"<<endl;
                return -1;
            }
            if (it.first == key)
            {
                return vec[index].second;
            }
            else
            {
                index = customHash(key, i, choose);
                //cout<<"Hello"<<endl;
                customCount++;
            }
        }
        return -1;
    }
    int customHash(string key, int i, string choose)
    {
        string s1 = "Hash1", s2 = "Hash2";
        int index;
        if (!(s1.compare(choose)))
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }
        int a = (index + 2 * AuxFunction(index, i) + 1 * i * i) % size;
        return a;
    }
    // void DisplayHash()
    // {
    //     for ( int i = 0; i < size; i++)
    //     {
    //         cout << "vec[" << i << "]";
    //         auto x = vec[i];
    //         cout << " --> " << x.first << " " << x.second;
    //         cout << endl;
    //     }
    // }
};

string randomWord(int n)
{
    char alpha[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    string str = "";
    for (int i = 0; i < n; i++)
    {
        str = str + alpha[rand() % 26];
    }
    return str;
}

bool Prime(int n)
{
    if (n <= 3)
    {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    for (int i = 5; i * i <= n; i = i + 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
   // freopen("output.txt", "w", stdout);
    srand(5);
    int N1, flag = 1, N, x, num = 10000,d;
    // string arr[10]={"abcde","riyad","afzal","imtiaz","jakaria","toufique","tahsin","iffat","nabil","oitijjho"};
    string arr[num];
    cout<<endl;
    cout<<"Enter Table Size: ";
    cin>>N1;
    if(N1<num)
    {
        d=N1;
    }
    else{
        d=num;
    }
    for (int i = 0; i < num; i++)
    {
        string s = randomWord(5 + rand() % 6);
        // cout<<s<<endl;
        arr[i] = s;
    }
    x = N1 - 1;
    while (flag)
    {
        if (Prime(N1))
        {
            flag = 0;
            N = N1;
        }
        N1++;
    }
    flag = 1;
    while (flag)
    {
        if (Prime(x))
        {
            flag = 0;
            N2 = x;
        }
        x--;
    }
    // cout << N << " " << N2 << endl;
    int collisionCh[2], collisionD[2], collisionC[2], countC[2], countCh[2], countD[2];
    string store[2] = {"Hash1", "Hash2"};
    for (int j = 0; j < 2; j++)
    {
        int k = 1, l = 1, h = 1;
        collisionCh[j] = 0;
        collisionC[j] = 0;
        collisionD[j] = 0;
        countC[j] = 0;
        countCh[j] = 0;
        countD[j] = 0;
        HashTable objChain(N);
        HashTable objDouble(N);
        HashTable objCustom(N);
        for (int i = 0; i <num; i++)
        {
            // int p = objDouble.FindDouble(arr[i], store[j]);
            // int q = objChain.FindChain(arr[i], store[j]);
            // int t = objCustom.FindCustom(arr[i], store[j]);
            // if (p == -1)
            // {
            int p = objDouble.InsertDouble(arr[i], k, store[j]);
            // cout<<p<<endl;
            if (p == 0)
            {
                collisionD[j] += objDouble.doubleCollision;
                k++;
            }
            if (p == -1)
            {
                k++;
            }
            //  }
            int q = objChain.InsertChain(arr[i], l, store[j]);
            if (q == 0)
            {
                collisionCh[j] += objChain.chainCollision;
                l++;
            }
            if (q == -1)
            {
                l++;
            }
            int r = objCustom.InsertCustom(arr[i], h, store[j]);
            if (r == 0)
            {
                collisionC[j] += objCustom.customCollision;
                h++;
            }
            if (r == -1)
            {
                h++;
            }
        }
        srand(5);
        int m = 0;
        while (m < 1000)
        {
            string s = arr[rand() % d];
            objDouble.FindDouble(s, store[j]);
            objChain.FindChain(s, store[j]);
            objCustom.FindCustom(s, store[j]);
            countD[j] = countD[j] + objDouble.doubleCount + 1;
            countCh[j] = countCh[j] + objChain.chainCount + 1;
            countC[j] = countC[j] + objCustom.customCount + 1;
            m++;
        }
        // objChain.DisplayHash1();
    }
     cout << endl;
    for (int i = 0; i <2; i++)
    {   
        cout<<"Using Hash Function "<<i+1<<endl;
        cout<<"---------------Chain method----------------------------"<<endl;
        cout <<"Number Of collision: "<< collisionCh[i] << endl;
        cout <<"Average Probs: "<<countCh[i] / 1000.0 << endl;
        cout<<"---------------Double Hasing method----------------------------"<<endl;
        cout <<"Number Of collision: "<<collisionD[i] << endl;
        cout <<"Average Probs: "<< countD[i] / 1000.0 << endl;
         cout<<"---------------Custom Hasing method----------------------------"<<endl;
        cout <<"Number Of collision: "<< collisionC[i] << endl;
        cout <<"Average Probs: "<< countC[i] / 1000.0 << endl;
        cout<<endl;
        cout<<endl;
    }
}