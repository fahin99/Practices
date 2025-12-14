#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* createLL(int n, int a[]){
    Node* head=(Node*)malloc(sizeof(Node));
    head->data=a[0];
    head->next=NULL;
    Node* current=head;
    for(int i=1;i<n;i++){
        Node* newNode=(Node*)malloc(sizeof(Node));
        newNode->data=a[i];
        newNode->next=NULL;
        current->next=newNode;
        current=current->next;
    }
    return head;
}

Node* insertAt(int n, int a[], int pos, int val){
    Node* head=createLL(n,a);
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=val;
    newNode->next=NULL;

    if(pos==0){
        newNode->next=head;
        return newNode;
    }

    Node* current=head;
    for(int i=0;i<pos-1 && current!=NULL;i++){
        current=current->next;
    }
    if(current==NULL){
        free(newNode);
        return head;
    }
    newNode->next=current->next;
    current->next=newNode;
    return head;
}

void printLL(Node* head){
    Node* current=head;
    while(current!=NULL){
        printf("%d -> ",current->data);
        current=current->next;
    }
    printf("NULL\n");
}

int main(){
    int n=5;
    int a[]={10,20,30,40,50};
    Node* head=createLL(n,a);
    printLL(head);
    int pos=2;
    int val=25;
    head=insertAt(n,a,pos,val);
    printLL(head);
    return 0;
}