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

Node* printLL(Node* head){
    Node* current=head;
    while(current!=nullptr){
        cout<<current->data<<" -> ";
        current=current->next;
    }
    cout<<"NULL"<<endl;
    return head;
}

Node* insertAt(int n, int a[], int pos, int val){
    Node* head=createLL(n,a);
    Node* newNode=new Node(val);

    if(pos==0){
        newNode->next=head;
        return newNode;
    }

    Node* current=head;
    for(int i=0;i<pos-1 && current!=nullptr;i++){
        current=current->next;
    }
    if(current==nullptr){
        delete newNode;
        return head;
    }
    newNode->next=current->next;
    current->next=newNode;
    return head;
}

Node *deleteAt(int n, int a[], int pos){
    Node* head=createLL(n,a);

    if(pos==0){
        Node* temp=head;
        head=head->next;
        delete temp;
        return head;
    }

    Node* current=head;
    for(int i=0;i<pos-1 && current!=nullptr;i++){
        current=current->next;
    }
    if(current==nullptr || current->next==nullptr){
        return head;
    }
    Node* temp=current->next;
    current->next=current->next->next;
    delete temp;
    return head;
}

Node* getNodeAt(Node* head, int index){
    Node* current=head;
    int count=0;
    while(current!=nullptr){
        if(count==index){
            return current;
        }
        count++;
        current=current->next;
    }
    return nullptr;
}

Node* inserAtFront(Node* head, int val){
    Node* newNode=new Node(val);
    newNode->next=head;
    return newNode;
}

Node* insertAtEnd(Node* head, int val){
    Node* newNode=new Node(val);
    if(head==nullptr){
        return newNode;
    }
    Node* current=head;
    while(current->next!=nullptr){
        current=current->next;
    }
    current->next=newNode;
    return head;
}

