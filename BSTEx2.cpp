#include <iostream>

using namespace std;


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

void InorderTraversal(BstNode* root, bool docount){
    if(root!=NULL){
    InorderTraversal(root->left, docount);
    if(docount) cout<<root->data<<"("<<root->count<<")"<<" ";
    else cout<<root->data<<" ";
    InorderTraversal(root->right, docount);
    }
}

int Counting(BstNode* root, int* count){
    if(root!=NULL){
    Counting(root->left, count);
    *count+=1;
    //*count+=root->count;
    Counting(root->right, count);
    }
}

int Arraying(BstNode* root, int* arr, int& i){
    if(root!=NULL){
        Arraying(root->left, arr, i);
        //for(int a=0; a<root->count;a++)
            arr[i++] = root->data;
        Arraying(root->right, arr, i);
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

BstNode* reorder(BstNode* root){
    int* count = new int;
    *count = 0;
    Counting(root, count);
    cout<<"\nNumber of Nodes: "<<*count<<endl;


    int* arr = new int[*count];
    int i = 0;
    Arraying(root, arr, i);
    /*cout<<"New Array: \n";
    for(int a=0; a<*count;a++){
        cout<< *(arr+a)<< " ";
    }*/
    int middlePoint = int(*count/2);
    cout<<"New root value: "<<*(arr+ middlePoint)<<endl;

    BstNode* newroot = NULL;
    for(int a=0; a<*count;a++){
        if(middlePoint - a>=0){
            int value_left = *(arr+ middlePoint - a);
            newroot = Insert(newroot,value_left);
        } 
        if(middlePoint + a < *count-1){
            int value_right = *(arr+ middlePoint + a + 1);
            newroot = Insert(newroot,value_right);
        }
    }
    return newroot;
}   

int main(){
    BstNode* root = NULL;
    int size = 25;
    int arr[size];
    int number;

    for(int i=0;i<size;i++)
        arr[i]=rand()%25;
    cout<<"\nElements of the array: "<<endl;
    for(int i=0;i<size;i++)
        cout<<"Element "<<i+1<<": "<<arr[i]<<endl;


    for(int i=0; i<size;i++){
        root = Insert(root, arr[i]);
    }
    cout<<"Tree :\n";
    InorderTraversal(root, true);
    cout<<"\n\nInsert: \n";
    root = Insert(root, 18);
    root = Insert(root, 11);
    root = Insert(root, 25);
    InorderTraversal(root, true);
    
    cout<<"\n\nDelete:\n";
    root = remove(root, 6);
    root = remove(root, 13);    
    root = remove(root, 16);
    InorderTraversal(root, true);
    cout<<"\n\nRoot after removal: "<<root->data<<endl;


    cout<<"Enter the number to be searched: "<<endl;
    cin>>number;
    if(Search(root, number)) cout<<"Found it"<<endl;
    else cout<<"Not found"<<endl;

    BstNode* newroot = reorder(root);
    cout<<"New Tree :\n";
    InorderTraversal(newroot, true);
}