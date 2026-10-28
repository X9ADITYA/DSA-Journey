
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

int main()
{
    Node *head = NULL, *temp, *newNode;
    int n, value, key, position = 1;
    bool found = false;

    cout << "Enter number of nodes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        newNode = new Node;

        cout << "Enter data: ";
        cin >> value;

        newNode->data = value;
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            temp = newNode;
        }
        else
        {
            temp->next = newNode;
            temp = newNode;
        }
    }

    cout << "Enter element to search: ";
    cin >> key;

    temp = head;

    while (temp != NULL)
    {
        if (temp->data == key)
        {
            cout << "Element found at position "
                 << position << endl;
            found = true;
            break;
        }

        temp = temp->next;
        position++;
    }

    if (!found)
    {
        cout << "Element not found.\n";
    }

    return 0;
}

