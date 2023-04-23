#include <iostream>

using namespace std;

static bool DoRemove = false;

struct BstNode{
    int data;
    int count;
    BstNode* left;
    BstNode* right;
}; 

BstNode* GetNewNode(int data){
    BstNode* newNode = new BstNode();
    newNode->data = data;// (*newNode).data = data;
    newNode->left = newNode->right = NULL;
    newNode->count = 1;
    return newNode;
}

BstNode* Insert(BstNode* root, int data){

    if(root == NULL){//empty tree, leaf
        root = GetNewNode(data);
        return root;
    }

    else if(data == root->data){
        root->count++;
        return root;
    }

    else if(data < root->data){
        root->left = Insert(root->left,data);
    }

    else root->right = Insert(root->right,data);

    return root; 
}

bool Search(BstNode* root, int data){
    if(root==NULL) return false;
    else if(root->data == data) return true;
    else if(root->data <= data) return Search(root->right,data);
    else return Search(root->left, data);
}

void InorderTraversal(BstNode* root, bool count){
    if(root!=NULL){
    InorderTraversal(root->left, count);
    if(count) cout<<root->data<<"("<<root->count<<")"<<" ";
    else cout<<root->data<<" ";
    InorderTraversal(root->right, count);
    }
}
BstNode* Min(BstNode* root){
    if(root->left==NULL) return root;
    return Min(root->left);
}


BstNode* remove(BstNode* root, int data){
    if(root==NULL){ 
        cout << "Not found: "<<data<<endl;
        return NULL;
    }    

    if(root->data > data){
        root->left = remove(root->left,data);
    }
    else if(root->data < data){
        root->right = remove(root->right,data);
    }
    else{
        if (root->left==NULL && root->right==NULL){ //Case1: No Child
            delete root;
            root = NULL;
        }
        else if (root->left == NULL){ //Case2: 1 Child
            BstNode* temp = root;
            root = root->right;
            delete temp;
        } 
        else if (root->right == NULL){
            BstNode* temp = root;
            root = root->left;
            delete temp;
        }
        else{ //Case3: 2 children
            BstNode* temp = Min(root->right);
            root->data = temp->data;
            root->right = remove(root->right, temp->data);
        }
    }
    return root; 

}

int main(){
    int arr[] = {13, 6, 15, 17, 20, 9, 4, 3, 7, 2, 18};
    int n = sizeof(arr) / sizeof(arr[0]);
    BstNode* root = NULL;
    for(int i=0; i<n;i++){
        root = Insert(root, arr[i]);
    }
    cout<<"Tree 1:\n";
    InorderTraversal(root, true);
    //More Balanced
    cout<<"\n\nInsert: \n";
    root = Insert(root, 18);
    root = Insert(root, 11);
    root = Insert(root, 25);
    InorderTraversal(root, true);
    root = remove(root, 6);
    root = remove(root, 13);    
    root = remove(root, 18);
    cout<<"\n\nDelete:\n";
    InorderTraversal(root, true);
    cout<<"\n\nRoot: "<<root->data<<endl;


    int arr2[] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    BstNode* root2 = NULL;
    for(int i=0; i<n2;i++){
        root2 = Insert(root2, arr2[i]);
    }
    cout<<"\n\nTree 2:\n";
    InorderTraversal(root2, true);
    cout<<"\n\nInsert: \n";
    root2 = Insert(root2, 18);
    root2 = Insert(root2, 11);
    root2 = Insert(root2, 25);
    InorderTraversal(root2, true);
    root2 = remove(root2, 6);
    root2 = remove(root2, 13);    
    root2 = remove(root2, 18);
    cout<<"\n\nDelete:\n";
    InorderTraversal(root2, true);
    cout<<"\n\nRoot: "<<root2->data<<endl;

}