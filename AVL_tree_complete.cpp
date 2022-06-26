#include<bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int h;
    int f;
};

struct Node* GetNewNode(int x)
{
    struct Node* temp = new struct Node[1];
    temp->data = x;
    temp->left = temp->right = NULL;
    temp->h = 1;
    temp->f = 0;
    return temp;
}

int HeightOfTree(Node* root)
{
    if(root == NULL)return 0;
    return max(HeightOfTree(root->left),HeightOfTree(root->right)) +1;
}
int heightFactor(struct Node* root);

struct Node* LLRotaion(struct Node* root)
{
   struct Node* rootl = root->left;
   struct Node* rootlr = rootl->right;

   rootl->right = root;
   root->left = rootlr;
   root->h = HeightOfTree(root);
   rootl->h = HeightOfTree(rootl);
   root->f = heightFactor(root);
   rootl->f = heightFactor(rootl);

   

   return rootl;
   
}
struct Node* RRRotation(struct Node* root)
{
    struct Node* r = root->right;
    struct Node* rl = r->left;

    root->right = rl;
    r->left = root;

    r->h = HeightOfTree(r);
    root->h = HeightOfTree(root);

    r->f = heightFactor(r);
    root->f = heightFactor(root);
    return r;
}
struct Node* LRRotation(struct Node* root)
{
    //LR rotaion == RR Rotaion + LL Rotaion 
   root->left = RRRotation(root->left);
   return root = LLRotaion(root);

}
struct Node* RLRotation(struct Node* root)
{
    //RL rotation == LL Rotation + RR Rotaion
    root->right = LLRotaion(root->right);

    return root = RRRotation(root);


}


int heightFactor(struct Node* root)
{
    return (HeightOfTree(root->left) - HeightOfTree(root->right));
}


struct Node* BST(struct Node* root, int data)
{
    if(root == NULL)
    {
        root = GetNewNode(data);
    }
    else if(root->data > data)
    {
        root->left = BST(root->left, data);
    }
    else{
        root->right = BST(root->right, data);
    }

    root->h = HeightOfTree(root);
    root->f = heightFactor(root);

    int hf = heightFactor(root);
   
    if(hf == 2 && heightFactor(root->left) == 1)
    {
        return LLRotaion(root);
    }
    else if(hf == 2 && heightFactor(root->left) == -1)
    {
        return LRRotation(root);
    }
    
    if(hf == -2 && heightFactor(root->right) == -1)
    {
       return RRRotation(root);
   }
    
    else if(hf == -2 && heightFactor(root->right) == 1)
    {
        return RLRotation(root);
    }
    

    return root;
}

void PrintBST(Node* root)
{
    if(root == NULL)return;

    PrintBST(root->left);

   cout<<" "<<root->data<<" h = "<<root->h<<" hf = "<<root->f<<endl;
    
    PrintBST(root->right);
}
void PrintIn(struct Node* root)
{
    if (root == NULL)return;
    cout<<" "<<root->data<<" h = "<<root->h<<" hf = "<<root->f<<endl;
    PrintIn(root->left);
    PrintIn(root->right);
}
void PrintPost(struct Node* root)
{
    if(root == NULL)return;

    PrintPost(root->left);
    PrintPost(root->right);
    cout<<" "<<root->data<<" h = "<<root->h<<" hf = "<<root->f<<endl;
}

/*int SetHeight(struct Node* root)
{
    if(root == NULL)return 0;
    return root->h = max(SetHeight(root->left),SetHeight(root->right)) + 1; 
}*/
/*int setHeightFactor(Node* root)
{
    if(root == NULL)return;

    root->h = HeightOfTree(root->left)-HeightOfTree(root->right);
}
*/

int main()
{
    Node* root = NULL;

   
    // root = BST(root,5);
    // root = BST(root,3);
    // root = BST(root,2);
    // root = BST(root,4);
    // root = BST(root,6);
    // root = BST(root,1);
    // root = BST(root,7);
    // root = BST(root,8);

    for(int i = 1; i< 20; i++)
    {
        root = BST(root, i);
    }

    cout<<endl<<endl;


    PrintBST(root);
    cout<<endl;
    PrintIn(root);
    cout<<endl;
    PrintPost(root);

    

    return 0;

}