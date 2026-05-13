#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct TreeNode
{
    int adat;
    TreeNode *parent, *left, *right;

    TreeNode(int adat, TreeNode *parent = 0, TreeNode *left = 0, TreeNode *right = 0)
    {
        this->adat = adat;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
    ~TreeNode()
    {
        delete left;
        delete right;
    }
};

class KeresoFa
{
    TreeNode *root;

    void inorder(TreeNode *root)
    {
        if(root == 0) return;
        inorder(root -> left);
        cout << root -> adat << " ";
        inorder(root -> right);
    }

    void printTree(TreeNode* node, string prefix = "", bool isLast = true, bool isRoot = true)
    {
        if(!node) return;

        cout << prefix;

        if(!isRoot)
            cout << (isLast ? "\xc0\xc4\xc4" : "\xc3\xc4\xc4");

        cout << node->adat << endl;

        if(!isRoot)
            prefix += (isLast ? "   " : "\xb3  ");

        //bal gyerek (ha van jobb akkor nem utolso, nem gyoker)
        if(node->left)
            printTree(node->left, prefix, node->right == nullptr, false);

        //jobb gyerek (utolso, nem gyoker)
        if(node->right)
            printTree(node->right, prefix, true, false);
    }

public:

    KeresoFa()
    {
        root = 0;
    }

    ~KeresoFa()
    {
        delete root;
    }

    void beszur(int adat, TreeNode *p = 0)
    {
        if(root == 0)
        {
            root = new TreeNode(adat);
            return;
        }

        if(p == 0) p = root;

        if(adat < p->adat)
        {
            if(p->left)
                beszur(adat, p->left);
            else
                p->left = new TreeNode(adat, p);
        }
        else
        {
            if(p->right)
                beszur(adat, p->right);
            else
                p->right = new TreeNode(adat, p);
        }
    }

    void kiir()
    {
        inorder(root);
        cout << endl;
    }

    void kiirFa()
    {
        printTree(root);
        cout << endl;
    }

    TreeNode *keres(int elem)
    {
        TreeNode *p = root;
        while(p != 0 && p->adat != elem)
        {
            if(p->adat < elem) p = p->right;
            else p = p->left;
        }
        return p;
    }

    TreeNode *minimum(TreeNode *p = 0)
    {
        if(p == 0) p = root;
        while(p != 0 && p->left != 0)
        {
            p = p->left;
        }
        return p;
    }

    TreeNode *maximum(TreeNode *p = 0)
    {
        if(p == 0) p = root;
        while(p != 0 && p->right != 0)
        {
            p = p->right;
        }
        return p;
    }

    TreeNode *elso()
    {
        return minimum();
    }

    TreeNode *utolso()
    {
        return maximum();
    }

    TreeNode *kovetkezo(TreeNode *node)
    {
        if(node == 0) return 0;
        else if(node->right)
        {
            return minimum(node->right);
        }
        else
        {
            TreeNode *p = node;
            while(p->parent != 0 && p->parent->right == p)
            {
                p = p->parent;
            }
            return p->parent;
        }
    }

    TreeNode *elozo(TreeNode *node)
    {
        if(node == 0) return 0;
        else if(node->left)
        {
            return maximum(node->left);
        }
        else
        {
            TreeNode *p = node;
            while(p->parent != 0 && p->parent->left == p)
            {
                p = p->parent;
            }
            return p->parent;
        }
    }

    void torol(TreeNode *node)
    {
        if(node == 0) return;
        //ha level
        if(node->left == 0 && node->right == 0)
        {
            TreeNode *p = node->parent;

            if(p == 0)  // a gyokeret toroljuk es egyben level is ezert a fa ures lesz
                root = 0;
            else
            {
                if(p->left == node)
                    p->left = 0;
                else
                    p->right=0;
            }
            delete node;
        }
        //ha ket gyermeke van
        else if(node->left != 0 && node->right != 0)
        {
            TreeNode *p = minimum(node->right);
            node->adat = p->adat;
            torol(p);
        }
        //ha egy gyermeke van
        else
        {
            TreeNode *child;
            TreeNode *p = node->parent;
            if(node->left != 0)
            {
                child = node->left;
                node->left=0;
            }
            else
            {
                child = node->right;
                node->right=0;
            }

            if(p == 0) //a gyokeret toroljuk es egy gyermeke van
            {
                root = child;
            }
            else
            {
                if(p->left == node)
                    p->left = child;
                else
                    p->right=child;
            }

            child->parent = p;

            delete node;
        }
    }
};

int main()
{
    srand(time(0));

    int tomb[100] = {40, 110, 30, 60, 90, 10, 50, 20, 120, 80, 70, 100};

    KeresoFa a;
    for(int i = 0; i < 12; i++)
    {
        //a.beszur(rand() % 100);
        a.beszur(tomb[i]);
    }

    a.kiir();
    a.kiirFa();

    TreeNode *p;
    int keresettElem = 10;

    p = a.keres(keresettElem);
    if(p == 0) cout << "nem tartalmazza a " << keresettElem << "-t" << endl;
    else  cout << keresettElem << " cime:" << p << endl;


    p = a.minimum();
    if(p == 0) cout << "nincs minimum" << endl;
    else cout << "minimum elem: " << p->adat << endl;


    p = a.maximum();
    if(p == 0) cout << "nincs maximum" << endl;
    else cout << "maximum elem: " << p->adat << endl;

    p = a.kovetkezo(a.keres(keresettElem));
    if(p == 0) cout << keresettElem << "-nek nincs kovetkezoje" << endl;
    else cout << keresettElem << " kovetkezoje: " << p->adat << endl;

    p = a.elozo(a.keres(keresettElem));
    if(p == 0) cout << keresettElem << "-nek nincs elozoje" << endl;
    else cout << keresettElem << " elozoje: " << p->adat << endl;

    cout << "bejaras: ";
    for(TreeNode *p = a.elso(); p != 0; p = a.kovetkezo(p))
    {
        cout << p->adat << " ";
    }
    cout << endl;

    for(int i = 0; i < 12; i++)
    {
        a.torol(a.keres(tomb[i]));
    }

    a.kiirFa();

    return 0;
}
