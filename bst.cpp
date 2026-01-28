#include<iostream>
using namespace std;

class node{
    int data;
    node* left;
    node* right;
    friend class bst;
};

class bst{
    node* root;
    node* insert_help(node* root,int val){
        if(root==nullptr){
            node* newn=new node();
            newn->data=val;
            newn->left=nullptr;
            newn->right=nullptr;
            return newn;
        }
        else{
            if(val<=root->data){
                root->left=insert_help(root->left,val);
            }
            else{
                root->right=insert_help(root->right,val);
            }
            return root;
        }
    }

    node* deletion_help(node* root,int val){
        if(root==nullptr) return root;
        if(val<root->data) root->left=deletion_help(root->left,val);
        else if(val>root->data) root->right=deletion_help(root->right,val);
        else{
            if(root->left==nullptr and root->right==nullptr){
                delete root;
                root=nullptr;
            }
            else if(root->left==nullptr){
                node* temp=root;
                root=root->right;
                delete temp;
            }
            else if(root->right==nullptr){
                node* temp=root;
                root=root->left;
                delete temp;
            }
            else{
                node* temp=root->right;
                while(temp->left!=nullptr){
                    temp=temp->left;
                }
                root->data=temp->data;
                root->right=deletion_help(root->right,temp->data);
            }
        }
        return root;
    }
    void swap(node*& a,node*& b){
        node* temp=a;
        a=b;
        b=temp;
    }
    public:
        bst(){
            root=nullptr;
        }
        bst(int val){
            root=new node();
            root->data=val;
            root->left=nullptr;
            root->right=nullptr;
        }
        void insert(int val){
            root=insert_help(root,val);
        }
        void deletion(int val){
            root=deletion_help(root,val);
        }
        void search(int val){
            node* temp=root;
            while(temp!=nullptr){
                if(temp->data==val){
                    cout<<"Found\n";
                    return;
                }
                else if(val<temp->data) temp=temp->left;
                else temp=temp->right;
            }
            cout<<"Not Found\n";
        }
        void reverse(node* root){
            if(root==nullptr) return;
            swap(root->left,root->right);
            reverse(root->left);
            reverse(root->right);
        }
};