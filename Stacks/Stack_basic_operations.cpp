
#include <iostream>
using namespace std;

#define SIZE 5

int stack[SIZE];
int top = -1;


void push(int value) {
    if (top == SIZE - 1) {
        cout << "Stack Overflow! Stack is full.\n";
    } else {
        top++;
        stack[top] = value;
        cout << value << " pushed into stack.\n";
    }
}


void pop() {
    if (top == -1) {
        cout << "Stack Underflow! Stack is empty.\n";
    } else {
        cout << stack[top] << " popped from stack.\n";
        top--;
    }
}


void display() {
    if (top == -1) {
        cout << "Stack is empty.\n";
    } else {
        cout << "Stack elements (top to bottom):\n";

        for (int i = top; i >= 0; i--) {
            cout << stack[i] << endl;
        }
    }
}

int main() {
    int choice, value;

    do {
        cout << "\n--- STACK MENU ---\n";
        cout << "1. PUSH\n";
        cout << "2. POP\n";
        cout << "3. DISPLAY\n";
        cout << "4. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                push(value);
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
