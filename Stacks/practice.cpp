#include<iostream>
using namespace std;
# define SIZE 5



int stack[SIZE];

int top = -1;


void push(int value){
	if(top == SIZE-1){
		cout<<"stack is overflow";
	}
	else {
		top++;
		stack[top]= value;
	}
}

void pop(){
	if(top==-1){
		cout<<"stack underflow";
	}
	else{
		cout<<"popped element"<<stack[top];
		top--;
	}
}


void display(){
	if(top==-1){
		cout<<"stack is empty";
		
	}
	else {
		cout<<"stack element";
		for (int i = top; i>= 0 ; i--){
			cout<<stack[i]<<endl;
		}
	}
}


int main()
{
    int choice, value;

    do
    {
        cout << "\n--- STACK MENU ---\n";
        cout << "1. PUSH\n";
        cout << "2. POP\n";
        cout << "3. DISPLAY\n";
        cout << "4. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter value: ";
            cin >> value;
            push(value);
        }
        else if (choice == 2)
        {
            pop();
        }
        else if (choice == 3)
        {
            display();
        }
        else if (choice == 4)
        {
            cout << "Exiting program.\n";
        }
        else
        {
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
