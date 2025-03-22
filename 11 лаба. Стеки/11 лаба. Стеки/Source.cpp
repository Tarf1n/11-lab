#include <iostream>
#include <clocale>

using namespace std;

struct Node
{
    char data;
    Node* next_ptr;
};

struct Stack
{
    Node* head;
    int size;
};

void SetNode(Node*& temp, char data, Node* next_ptr)
{
    temp = new Node;
    temp->data = data;
    temp->next_ptr = next_ptr;
}

void SetStack(Stack& MyStack)
{
    MyStack.head = nullptr;
    MyStack.size = 0;
}

void Push(Stack& MyStack, const char data)
{
    Node* new_node;
    SetNode(new_node, data, MyStack.head);
    MyStack.head = new_node;
    MyStack.size++;
}

void PopKElements(Stack& MyStack, int k)
{
    if (k <= 0 || MyStack.head == nullptr) return;

    while (MyStack.head != nullptr && k > 0)
    {
        Node* delete_element = MyStack.head;
        MyStack.head = MyStack.head->next_ptr;
        delete delete_element;
        MyStack.size--;
        k--;
    }
}

void AddAfterElement(Stack& MyStack, char targetChar, char newValue)
{
    if (MyStack.head == nullptr) return;

    Stack tempStack;
    SetStack(tempStack);

    bool elementFound = false;

    while (MyStack.head != nullptr)
    {
        Node* current = MyStack.head;
        MyStack.head = MyStack.head->next_ptr;

        if (current->data == targetChar && !elementFound)
        {
            Node* newNode;
            SetNode(newNode, newValue, nullptr);
            Push(tempStack, newNode->data);
            elementFound = true;
        }

        Push(tempStack, current->data);
        delete current;
    }

    while (tempStack.head != nullptr)
    {
        Node* current = tempStack.head;
        tempStack.head = tempStack.head->next_ptr;
        Push(MyStack, current->data);
        delete current;
    }
}

void Show(const Stack& MyStack)
{
    Node* temp = MyStack.head;
    while (temp != nullptr)
    {
        cout << temp->data;
        if (temp->next_ptr != nullptr) {
            cout << " -> ";
        }
        temp = temp->next_ptr;
    }
    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Ru");

    Stack MyStack;
    SetStack(MyStack);

    Push(MyStack, 'd');
    Push(MyStack, 'c');
    Push(MyStack, 'b');
    Push(MyStack, 'a');

    cout << "Содержимое стека: ";
    Show(MyStack);

    int k = 2;
    PopKElements(MyStack, k);

    cout << "Содержимое стека после удаления " << k << " элементов: ";
    Show(MyStack);

    char targetChar = 'd';
    char newValue = 'x';
    AddAfterElement(MyStack, targetChar, newValue);

    cout << "Содержимое стека после добавления '" << newValue << "' после '" << targetChar << "': ";
    Show(MyStack);

    return 0;
}