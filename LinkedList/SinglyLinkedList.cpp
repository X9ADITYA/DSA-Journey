#include<iostream>
using namespace std;

struct Node{
	int data;
	Node* next;
};

int main(){
	Node *head=NULL,*temp,*newnode;
	int n , v;
	cout<<"enter the nodes";
	cin>>n;
	
	for(int i =0;i<n;i++){
		newnode = new Node;
		
		cout<<"enter the data";
		cin>>v;
		
		newnode->data=v;
		newnode->next=NULL;
		if(head==NULL){
			head=newnode;
			temp=newnode;
			
		}
		else{
			temp->next=newnode;
			temp=newnode;
		}
	}
	cout << "Linked List: ";

    temp = head;

    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }

    cout << "NULL" << endl;

    return 0;
}


