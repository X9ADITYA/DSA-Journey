
#include <iostream>
using namespace std;

#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

void enqueue(int value)
{
    if (rear == SIZE - 1)
    {
        cout << "Queue Overflow!\n";
    }
    else
    {
        if (front == -1)
            front = 0;

        rear++;
        queue[rear] = value;

        cout << value << " inserted into queue.\n";
    }
}

void dequeue()
{
    if (front == -1 || front > rear)
    {
        cout << "Queue Underflow!\n";
    }
    else
    {
        cout << "Deleted element: " << queue[front] << endl;
        front++;

        if (front > rear)
        {
            front = -1;
            rear = -1;
        }
    }
}

void display()
{
    if (front == -1)
    {
        cout << "Queue is empty.\n";
    }
    else
    {
        cout << "Queue elements: ";

        for (int i = front; i <= rear; i++)
        {
            cout << queue[i] << " ";
        }

        cout << endl;
    }
}

int main()
{
    int choice, value;

    do
    {
        cout << "\n--- QUEUE MENU ---\n";
        cout << "1. ENQUEUE\n";
        cout << "2. DEQUEUE\n";
        cout << "3. DISPLAY\n";
        cout << "4. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter value: ";
            cin >> value;
            enqueue(value);
        }
        else if (choice == 2)
        {
            dequeue();
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

