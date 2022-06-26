#include<iostream>
using namespace std;


struct Node{

    int data;
    int height;
    int hf;

    struct Node* lchild;
    struct Node* rchild;
};

struct Node* LLRotation(struct Node* root);
struct Node* RRRotation(struct Node* root);
struct Node* LRRotation(struct Node* root);
struct Node* RLRotation(struct Node* root);

int heightOfNode(struct Node* root);
int heightFatorNode(struct Node* root);

void PrintPreOrder(struct Node* root);
void PrintInOrder(struct Node* root);
void PrintPostOrder(struct Node* root);

struct Node* GetNewNode(int data);
struct Node* CreateAVLTree(struct Node* root, int data);


int main()
{
    struct Node* root = NULL;

    for(int i =1; i<32; i++)
    {
        root = CreateAVLTree(root, i);
    }

    PrintPreOrder(root);
    cout<<endl;
    PrintInOrder(root);
    cout<<endl;
    PrintPostOrder(root);

    return 0;
}


struct Node* GetNewNode(int data)
{
    struct Node* temp = new struct Node[1];
    temp->data = data;
    temp->height = 0;
    temp->hf = 0;
    temp->lchild = temp->rchild = NULL;

    return temp;
}

struct Node* CreateAVLTree(struct Node* root, int data)
{
    if(root == NULL)
    {
        root = GetNewNode(data);
    }
    else if(root->data > data)
    {
        root->lchild = CreateAVLTree(root->lchild, data);
    }
    else {
        root->rchild = CreateAVLTree(root->rchild, data);
    }

    root->height = heightOfNode(root);
    root->hf = heightFatorNode(root);

    if(root->hf == 2 && root->lchild->hf == 1)
    {
        return LLRotation(root);
    }
    else if(root->hf == 2 && root->lchild->hf == -1)
    {
        return LRRotation(root);
    }
    else if(root->hf == -2 && root->rchild->hf == -1)
    {
        return RRRotation(root);
    }
    else if(root->hf == -2 && root->rchild->hf == 1)
    {
        return RLRotation(root);
    }

    return root;
}

int heightOfNode(struct Node* root)
{
    if(root == NULL)return 0;
    else return max(heightOfNode(root->lchild), heightOfNode(root->rchild))+1;
}
int heightFatorNode(struct Node* root)
{
    return (heightOfNode(root->lchild) - heightOfNode(root->rchild));
}


struct Node* LLRotation(struct Node* root)
{
    struct Node* rootLchild = root->lchild;
    root->lchild = rootLchild->rchild;
    rootLchild->rchild = root;

    root->hf = heightFatorNode(root);
    rootLchild->hf = heightFatorNode(rootLchild);
    root->height = heightOfNode(root);
    rootLchild->height = heightOfNode(rootLchild);

    return rootLchild;
}
struct Node* RRRotation(struct Node* root)
{
    struct Node* rootRchild = root->rchild;
    root->rchild = rootRchild->lchild;
    rootRchild->lchild = root;

    root->hf = heightFatorNode(root);
    rootRchild->hf = heightFatorNode(rootRchild);
    root->height = heightOfNode(root);
    rootRchild->height = heightOfNode(rootRchild);

    return rootRchild;
}
struct Node* LRRotation(struct Node* root)
{
    root->lchild = RRRotation(root->lchild);

    return root = LLRotation(root);
}
struct Node* RLRotation(struct Node* root)
{
    root->rchild = LLRotation(root->rchild);

    return root = RRRotation(root);
}

void PrintPreOrder(struct Node* root)
{
    if(root == NULL)return;

    cout<<" "<<root->data<<" height = "<<root->height<<" hfactor = "<<root->hf<<endl;

    PrintPreOrder(root->lchild);
    PrintPreOrder(root->rchild);
}
void PrintPostOrder(struct Node* root)
{
    if(root == NULL)return;
    PrintPreOrder(root->lchild);
    PrintPreOrder(root->rchild);

    cout<<" "<<root->data<<" height = "<<root->height<<" hfactor = "<<root->hf<<endl;
}

void PrintInOrder(struct Node* root)
{
    if(root == NULL)return;

    PrintPreOrder(root->lchild);

    cout<<" "<<root->data<<" height = "<<root->height<<" hfactor = "<<root->hf<<endl;
    
    PrintPreOrder(root->rchild);
}

