#include <bits\stdc++.h>

using namespace std;

class Node
{
public:
    int key;
    int degree;
    Node *parent;
    Node *child;
    Node *sibling;
};
class BinomialHeap
{
public:
    Node *Head;
    Node *headRev;

    BinomialHeap()
    {
        Head =NULL;
        headRev =NULL;
    }
    void connectHeap(Node *&p, Node *&q)
    {
        p->parent = q;
        p->sibling = q->child;
        q->child = p;
        q->degree += 1;
    }
    Node *getNode(int n)
    {
        Node *ptr = new Node;
        ptr->key = n;
        return ptr;
    }
    void printNode(Node *H,ofstream &fout)
    {
        queue<Node *> Queue;
        Queue.push(H);
        int level = 0;
        while (!Queue.empty())
        {
            int sz = Queue.size();
            //cout << "Level " << level << ": ";
            fout << "Level " << level << ": ";

            for (int i = 0; i < sz; i++)
            {
                Node *temp = Queue.front();
                Node *x = temp->child;
                Queue.pop();
                //cout << temp->key << " ";
                fout << temp->key << " ";
                while (x != NULL)
                {
                    // cout<<"Helo"<<endl;
                    Queue.push(x);
                    x = x->sibling;
                }
            }
            //cout << endl;
            fout<<endl;
            level += 1;
        }
    }
    Node *Merge(Node *H1, Node *H2)
    {
        Node *p = H1;
        Node *q = H2;
        Node *temp = NULL;
        Node *H = NULL;
        if (p == NULL)
        {
            temp = q;
            q = q->sibling;
        }
        else if (q == NULL)
        {
            temp = p;
            p = p->sibling;
        }
        else
        {
            if (p->degree <= q->degree)
            {
                temp = p;
                p = p->sibling;
            }
            else
            {
                temp = q;
                q = q->sibling;
            }
        }

        H = temp;
       // cout << "T" << endl;
        while (p != NULL && q != NULL)
        {
            if (p->degree <= q->degree)
            {
                temp->sibling = p;
                p = p->sibling;
            }
            else
            {
                temp->sibling = q;
                q = q->sibling;
            }

            temp = temp->sibling;
        }

        if (p != NULL)
        {
            while (p != NULL)
            {
                temp->sibling = p;
                p = p->sibling;
                temp = temp->sibling;
            }
        }

        if (q != NULL)
        {
            while (q != NULL)
            {
                temp->sibling = q;
                q = q->sibling;
                temp = temp->sibling;
            }
        }
        return H;
    }
    Node *Union(Node *H1, Node *H2)
    {
        Node *prev_x, *next_x, *x;
        Node *H =NULL;
        H = Merge(H1, H2);
        if (H == NULL)
        {
            return H;
        }
        x = H;
        prev_x = NULL;
        next_x = x->sibling;
        while (next_x != NULL)
        {
            // cout<<next_x->key<<endl;
            if (x->degree != next_x->degree)
            {
                prev_x = x;
                x = next_x;
            }
            else if ((next_x->sibling != NULL) && (x->degree == next_x->degree) && (x->degree == (next_x->sibling)->degree))
            {

                prev_x = x;
                x = next_x;
            }
            else
            {
                if (x->key <= next_x->key)
                {
                    x->sibling = next_x->sibling;
                    connectHeap(next_x, x);
                }
                else
                {
                    if (prev_x == NULL)
                    {
                        H = next_x;
                    }
                    else
                    {
                        prev_x->sibling = next_x;
                    }
                    connectHeap(x, next_x);
                    x = next_x;
                }
            }
            next_x = x->sibling;
        }
        // Node *temp=H;
        // while(temp!=NULL)
        // {
        //     cout<<temp->key<<" ";
        //     temp=temp->sibling;
        // }
        // cout<<endl;
        return H;
    }
    int FindMin(Node *H)
    {
        Node *temp = H;
        int num = H->key;
        while (temp != NULL)
        {
            if (temp->key < num)
            {
                num = temp->key;
            }
            temp = temp->sibling;
        }
        return num;
    }
    Node *Insert(Node *H, Node *x)
    {
        Node *H1 =NULL;
        x->parent = NULL;
        x->child = NULL;
        x->sibling = NULL;
        x->degree = 0;
        H1 = x;
        H = Union(H, H1);
        // cout << "In Insert" << endl;
        return H;
    }
    void Print(Node *H,ofstream &fout)
    {
        // cout << "In Display" << endl;
        if (H == NULL)
        {
           // cout << "Printing Bionominal heap......." << endl;
            fout << "Printing Bionominal heap......." << endl;
            return;
        }
        Node *p;
        p = H;
        int k = 0;
        fout << "Printing Bionominal heap......." << endl;
        //cout << "Printing Bionominal heap......." << endl;
        while (p != NULL)
        {
            // cout << p->key << endl;
            //cout << "Bionominal tree, B" << p->degree << endl;
            fout << "Bionominal tree, B" << p->degree << endl;
            printNode(p,fout);
            p = p->sibling;
        }
    }
    void Reverse(Node *y)
    {
        if (y->sibling != NULL)
        {
            Reverse(y->sibling);
            (y->sibling)->sibling = y;
        }
        else
        {
            headRev = y;
        }
    }
    Node *Extract_Min(Node *H1)
    {
        Node *t = NULL;
        Node *x = H1;
        headRev = NULL;
        if (x == NULL)
        {
            cout << "The bionominal heap is empty" << endl;
            return x;
        }
        int minValue = x->key;
        Node *p = x;
        while (p->sibling != NULL)
        {
            if ((p->sibling)->key < minValue)
            {
                minValue = (p->sibling)->key;
                t = p;
                x = p->sibling;
            }
            p = p->sibling;
        }
        if (t == NULL && x->sibling == NULL)
        {
            H1 = NULL;
        }
        else if (x->sibling == NULL)
        {
            t->sibling = NULL;
        }
        else if (t == NULL)
        {
            H1 = x->sibling;
        }
        else
        {
            t->sibling = x->sibling;
        }
        if (x->child != NULL)
        {
            Reverse(x->child);
            (x->child)->sibling = NULL;
        }
        Head = Union(H1, headRev);
        // Node *temp=Head;
        //  while(temp!=NULL)
        //  {
        //      cout<<temp->key<<" ";
        //      temp=temp->sibling;
        //  }
        //  cout<<endl;
        return x;
    }
};

int main()
{
    ifstream fin("input.txt");
    if (!fin.is_open())
    {
        cout << "Unable to open the file." << endl;
        return 0;
    }

    ofstream fout("output.txt");

    int n, m, l, i;
    string str;
    BinomialHeap obj;
    Node *H, *H1, *p;
    H = obj.Head;
    while (getline(fin, str))
    {
        int num;
        char ch;
        ch = str[0];
        switch (ch)
        {
        case 'I':
        {
            num = stoi(str.substr(2));
            p = obj.getNode(num);
            H = obj.Insert(H, p);
            // cout << "Hello" << H->key << endl;
            break;
        }
        case 'E':
        {
            p = obj.Extract_Min(H);
            H = obj.Head;
            if (p != NULL)
            {
                //cout << "Extract-min returned " << p->key << endl;
                fout << "Extract-min returned " << p->key << endl;

            }
            else{
                cout<<"Heap is empty"<<endl;
            }
            break;
        }
        case 'U':
        {
            stringstream strList(str);
            string s;
            vector<int> arr;
            H1 = NULL;
            while (strList >> s)
            {
                if (!isalpha(s[0]))
                {
                    arr.push_back(stoi(s));
                }
            }
            for (int i = 0; i < arr.size(); i++)
            {
                // cout<<"arr"<<endl;
                p = obj.getNode(arr[i]);
                H1 = obj.Insert(H1, p);
            }
            // cout << endl;
            H = obj.Union(H, H1);
            break;
        }
        case 'F':
        {
            //cout << "Find-min returned " << obj.FindMin(H) << endl;
            fout << "Find-min returned " << obj.FindMin(H) << endl;
            break;
        }
        case 'P':
        {
            obj.Print(H,fout);
            break;
        }
        default:
            cout << "Wrong Choice";
        }
    }
    return 0;
}