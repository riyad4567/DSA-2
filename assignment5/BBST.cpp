#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <iomanip>
using namespace std;

class Node
{
public:
    int key;
    int height;
    Node *left;
    Node *right;

    Node()
    {
        key = 0;
        height = 0;
        left = NULL;
        right = NULL;
    }
    Node(int v)
    {
        key = v;
        height = 1;
        left = NULL;
        right = NULL;
    }
};
class BBST
{
public:
    Node *root;
    string s;
    BBST()
    {
        root = NULL;
        s = "";
    }
    int getHeight(Node *n)
    {
        if (n == NULL)
        {
            return 0;
        }
        return n->height;
    }

    int BalanceFactor(Node *n)
    {
        if (n == NULL)
        {
            return 0;
        }
        return (getHeight(n->left) - getHeight(n->right));
    }

    Node *leftRotation(Node *n)
    {
        Node *x = n->right;
        Node *y = x->left;
        x->left = n;
        n->right = y;
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }
    Node *rightRotation(Node *n)
    {
        Node *x = n->left;
        Node *y = x->right;
        x->right = n;
        n->left = y;
        n->height = max(getHeight(n->left), getHeight(n->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }
    Node *Insert(Node *temp, int n)
    {
        if (temp == NULL)
            return (new Node(n));

        if (temp->key > n)
            temp->left = Insert(temp->left, n);
        else if (temp->key < n)
            temp->right = Insert(temp->right, n);

        temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
        int factor = BalanceFactor(temp);
        // Left Left case
        if (factor > 1 && temp->left->key > n)
        {   
            //cout<<"LL"<<endl;
            return rightRotation(temp);
        }
        // Left Right Case
        else if (factor > 1 && temp->left->key < n)
        {   
           // cout<<"LR"<<endl;
            temp->left = leftRotation(temp->left);
            return rightRotation(temp);
        }
        // Right Left Case
        else if (factor < -1 && temp->right->key > n)
        {   
            //cout<<"RL"<<endl;
            temp->right = rightRotation(temp->right);
            return leftRotation(temp);
        }
        // Right Right Case
        else if (factor < -1 && temp->right->key < n)
        {   
            //cout<<"RR"<<endl;
            return leftRotation(temp);
        }
        return temp;
    }
    bool Find(int n)
    {
        if (root == NULL)
        {
            return false;
        }
        else
        {
            Node *temp = root;
            while (temp != NULL)
            {
                if (temp->key == n)
                {
                    return true;
                }
                else if (n < temp->key)
                {
                    temp = temp->left;
                }
                else
                {
                    temp = temp->right;
                }
            }
        }
        return false;
    }
    Node *Delete(Node *rt, int val)
    {
        if (rt == NULL)
        {
            return NULL;
        }
        else if (rt->key > val)
        {
            rt->left = Delete(rt->left, val);
        }
        else if (rt->key < val)
        {
            rt->right = Delete(rt->right, val);
        }
        else
        {
            if (rt->left == NULL && rt->right == NULL)
            {
                //cout << "leaf" << endl;
                delete rt;
                rt = NULL;
            }
            else if (rt->left == NULL)
            {
               // cout << "Rchild" << endl;
                Node *temp = rt->right;
                delete rt;
                rt = temp;
            }
            else if (rt->right == NULL)
            {
               // cout << "Lchild" << endl;
                Node *temp = rt->left;
                delete rt;
                rt = temp;
            }
            else
            {
                // find min
               // cout << "bothChild" << endl;
                Node *curr = rt->right;
                while (curr->left != NULL)
                {
                    curr = curr->left;
                }
                rt->key = curr->key;
                rt->right = Delete(rt->right, rt->key);
            }
        }
        if (rt == NULL)
        {
            return rt;
        }
        rt->height = max(getHeight(rt->left), getHeight(rt->right))+1;
        int bf = BalanceFactor(rt);
        // Left Left Case
        if (bf > 1 && BalanceFactor(rt->left) >= 0)
        {
            cout << "LL" << endl;
            return rightRotation(rt);
        }
        // Left Right Case
        else if (bf > 1 && BalanceFactor(rt->left) < 0)
        {
            cout << "LR" << endl;
            rt->left = leftRotation(rt->left);
            return rightRotation(rt);
        }
        // Right Left Case
        else if (bf < -1 && BalanceFactor(rt->right) > 0)
        {
            cout << "RL" << endl;
            rt->right = rightRotation(rt->right);
            return leftRotation(rt);
        }
        // Right Right Case
        else if (bf < -1 && BalanceFactor(rt->right) <= 0)
        {
           // cout << "RR" << endl;
            return leftRotation(rt);
        }
        return rt;
    }
    string InOrder(Node *n, string &s3)
    {

        if (n == NULL)
            return "";
        InOrder(n->left, s3);
        s3 += to_string(n->key) + " ";
        InOrder(n->right, s3);
        return s3;
    }
};

void print(Node *n, string &str)
{
    if (n == NULL)
    {
        return;
    }

    str += to_string(n->key);
    if (n->left == NULL && n->right == NULL)
    {
        return;
    }

    str += "(";
    print(n->left, str);
    str += ",";
    print(n->right, str);
    str += ")";
}

int main()
{
    BBST obj;
    string s = "", s1 = "", s2 = "", str;

    ifstream fin("input.txt");
    if (!fin.is_open())
    {
        cout << "Unable to open the file." << endl;
        return 0;
    }
    ofstream fout("output.txt");
    double sum1= 0,sum2=0,sum3=0,sum4=0;
    while (getline(fin, str))
    {
        int num;
        char ch;
        ch = str[0];
        switch (ch)
        {
        case 'I':
        {
            // fin >> num;
            num = stoi(str.substr(2));
            auto start1 = chrono::high_resolution_clock::now();
            ios_base::sync_with_stdio(false);
            // cout << ch << num << endl;
            obj.root = obj.Insert(obj.root, num);
            auto end1 = chrono::high_resolution_clock::now();
            double t1 = chrono::duration_cast<chrono::nanoseconds>(end1-start1).count();
            sum1 += t1;
            // time_taken *= 1e-6;
            s1 = "";
            print(obj.root, s1);
            fout << s1 << endl;
            break;
        }
        case 'F':
        {
            // fin >> num;
            num = stoi(str.substr(2));
            auto start2 = chrono::high_resolution_clock::now();
            ios_base::sync_with_stdio(false);
            // cout << ch << num << endl;
            bool f = obj.Find(num);
           // obj.root = obj.Insert(obj.root, num);
            auto end2 = chrono::high_resolution_clock::now();
            double t2 = chrono::duration_cast<chrono::nanoseconds>(end2-start2).count();
            sum2 += t2;
            // time_taken *= 1e-6;
            if (f)
            {
                fout << "found" << endl;
            }
            else
            {
                fout << "not found" << endl;
            }
            break;
        }
        case 'T':
        {
            s = "";
            // cout << ch << endl;
            auto start3 = chrono::high_resolution_clock::now();
            ios_base::sync_with_stdio(false);
            obj.InOrder(obj.root, s);
            //obj.root = obj.Insert(obj.root, num);
            auto end3 = chrono::high_resolution_clock::now();
            double t3 = chrono::duration_cast<chrono::nanoseconds>(end3-start3).count();
            sum3 += t3;
            // time_taken *= 1e-6;
            fout << s << endl;
            break;
        }
        case 'D':
        {
            // fin >> num;
            num = stoi(str.substr(2));
            // cout << ch << num << endl;
            auto start4 = chrono::high_resolution_clock::now();
            ios_base::sync_with_stdio(false);
            obj.root = obj.Delete(obj.root, num);
            auto end4 = chrono::high_resolution_clock::now();
            double t4 = chrono::duration_cast<chrono::nanoseconds>(end4 - start4).count();
            sum4 += t4;
            s2 = "";
            print(obj.root, s2);
            fout << s2 << endl;
            break;
        }
        }
    }
    fout<<"operation time(ms)"<<endl;
    fout<<"insert "<<sum1*(1e-6)<<endl;
    fout<<"delete "<<sum4*(1e-6)<<endl;
    fout<<"search "<<sum2*(1e-6)<<endl;
    fout<<"traverse "<<sum3*(1e-6)<<endl;
    fout<<"total "<<(sum1+sum2+sum3+sum4)*(1e-6)<<endl;
}