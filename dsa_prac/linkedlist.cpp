#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
        int data;
        Node* next;
        Node(int val){
            data=val;
            next=nullptr;
        }
};

Node* createLL(int n, int a[]){
    Node* head=new Node(a[0]);
    Node* current=head;
    for(int i=1;i<n;i++){
        current->next=new Node(a[i]);
        current=current->next;
    }
    return head;
}