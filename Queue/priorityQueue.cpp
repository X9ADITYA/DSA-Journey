
#include <iostream>
using namespace std;

#define SIZE 5

int value[SIZE];
int priority[SIZE];
int count = 0;

void insert(int val, int p)
{
    if (count == SIZE)
    {
        cout << "Priority Queue Overflow!\n";
        return;
    }

    value[count] = val;
    priority[count] = p;
    count++;

    cout << val << " inserted successfully.\n";
}

void deleteElement()
{
    if (count == 0)
    {
        cout << "Priority Queue is empty!\n";
        return;
    }

    int highest = 0;

    for (int i = 1; i < count; i++)
    {
        if (priority[i] < priority[highest])
        {
            highest = i;
        }
    }

    cout << "Deleted element: " << value[highest] << endl;

    for (int i = highest; i < count - 1; i++)
    {
        value[i] = value[i + 1];
        priority[i] = priority[i + 1];
    }

    count--;
}

void display()
{
    if (count == 0)
    {
        cout << "Priority Queue is empty.\n";
        return;
    }

    cout << "\nElement\tPriority\n";

    for (int i = 0; i < count; i++)
    {
        cout << value[i] << "\t" << priority[i] << endl;
    }
}

int main()
{
    int choice, val, p;

    do
    {
        cout << "\n--- PRIORITY QUEUE MENU ---\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter element: ";
            cin >> val;

            cout << "Enter priority (smaller number = higher priority): ";
            cin >> p;

            insert(val, p);
        }
        else if (choice == 2)
        {
            deleteElement();
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

