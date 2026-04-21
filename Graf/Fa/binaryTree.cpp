#include <iostream>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data)
    {
        this -> data = data;
        this -> left = 0;
        this -> right = 0;
    }
    TreeNode(int data, TreeNode *left, TreeNode *right)
    {
        this -> data = data;
        this -> left = left;
        this -> right = right;
    }
    ~TreeNode()
    {
        if(left)
            delete left;
        if(right)
            delete right;
    }
};

void preorder(TreeNode *root)
{
    if(root == 0)
        return;
    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root -> right);
}

void inorder(TreeNode *root)
{
    if(root == 0)
        return;
    inorder(root -> left);
    cout << root -> data << " ";
    inorder(root -> right);
}

void postorder(TreeNode *root)
{
    if(root == 0)
        return;
    postorder(root -> left);
    postorder(root -> right);
    cout << root -> data << " ";
}

void printTree(TreeNode* node, string prefix = "", bool isLast = true, bool isRoot = true)
{
    if(!node) return;

    cout << prefix;

    if(!isRoot)
        cout << (isLast ? "\xc0\xc4\xc4" : "\xc3\xc4\xc4");

    cout << node->data << endl;

    if(!isRoot)
        prefix += (isLast ? "   " : "\xb3  ");

    //bal gyerek (ha van jobb akkor nem utolso, nem gyoker)
    if(node->left)
        printTree(node->left, prefix, node->right == nullptr, false);

    //jobb gyerek (utolso, nem gyoker)
    if(node->right)
        printTree(node->right, prefix, true, false);
}

TreeNode* buildTree(int preo[] , int ino[], int preStart, int preEnd, int inStart, int inEnd)
{
    if(preStart > preEnd || inStart > inEnd) return 0;
    TreeNode* root = new TreeNode(preo[preStart]);
    int i;
    for(i = inStart; i <= inEnd && ino[i] != preo[preStart]; i++);
    int szakasz = i - inStart;
    root -> left = buildTree(preo, ino, preStart + 1, preStart + szakasz , inStart, i - 1);
    root -> right = buildTree(preo, ino, preStart + szakasz + 1, preEnd, i + 1, inEnd);
}

TreeNode* buildTreeFromOrder(int preo[] , int ino[], int n)
{
    return buildTree(preo, ino, 0, n-1, 0, n-1);
}

int main()
{
    /*
    cout << "ASCII table" << endl;
    for(unsigned char c = 0; c < 255; c++)
        cout << hex << (int)c << ": " << c << endl;
    */

    TreeNode *root;
    /*root = new TreeNode(1,
        new TreeNode(2,
            new TreeNode(4),
            new TreeNode(5)),
        new TreeNode(3,
            new TreeNode(6),
            new TreeNode(7)));*/
    root = new TreeNode(10,
    new TreeNode(5,
        new TreeNode(2,
            new TreeNode(1),
            nullptr),
        new TreeNode(7,
            new TreeNode(6),
            new TreeNode(8,
                nullptr,
                new TreeNode(9)))),
    new TreeNode(15,
        new TreeNode(12,
            new TreeNode(11),
            new TreeNode(13,
                nullptr,
                new TreeNode(14))),
        new TreeNode(20,
            new TreeNode(18,
                new TreeNode(17),
                nullptr),
            new TreeNode(25,
                new TreeNode(22),
                new TreeNode(30)))));

    cout << "Tree structure:" << endl;
    printTree(root);

    cout << endl << "Preorder:" << endl;
    preorder(root);
    cout << endl << "Inorder:" << endl;
    inorder(root);
    cout << endl << "Postorder:" << endl;
    postorder(root);

    int preo[100] = {1, 2, 4, 5, 3, 6, 7};
    int ino[100] = {4, 2, 5, 1, 6, 3, 7};

    delete root;
    root = buildTreeFromOrder(preo, ino, 7);
    cout << endl;
    printTree(root);
    return 0;
}
