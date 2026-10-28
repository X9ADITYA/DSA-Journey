
#include <iostream>
using namespace std;

#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

void enqueue(int value)
{
    if ((rear + 1) % SIZE == front)
    {
        cout << "Circular Queue Overflow!\n";
    }
    else
    {
        if (front == -1)
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % SIZE;
        }

        queue[rear] = value;
        cout << value << " inserted into queue.\n";
    }
}

void dequeue()
{
    if (front == -1)
    {
        cout << "Circular Queue Underflow!\n";
    }
    else
    {
        cout << "Deleted element: " << queue[front] << endl;

        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % SIZE;
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

        int i = front;

        while (true)
        {
            cout << queue[i] << " ";

            if (i == rear)
                break;

            i = (i + 1) % SIZE;
        }

        cout << endl;
    }
}

int main()
{
    int choice, value;

    do
    {
        cout << "\n--- CIRCULAR QUEUE MENU ---\n";
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

