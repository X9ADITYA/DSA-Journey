#include<iostream>
using namespace std;

int stack[32];
int top = -1;

void push(int value){
	stack[++top]=value;
}

 pop(){
	return stack[top--];
}

int main(){
	int n; 
	cout<<"enter the n:"<<endl;
	cin>>n;
	
	if(n==0){
		cout<<"binary:0"<<n;
	}
	
	while(n>0){
		int remainder=n%2;
		push(remainder);
		n=n/2; 
	}
	
	while(top!=-1){
		cout<<pop();
	}
	cout<<endl;
}


