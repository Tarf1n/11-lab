#include <iostream>
#include <clocale>

using namespace std;

struct Node {
    char data;
    Node* next;
};

struct Queue {
    int size;
    Node* head; 
    Node* tail; 
};

bool IsEmpty(const Queue& q) {
    return q.head == nullptr;
}

void InitializeQueue(Queue& q) {
    q.size = 0;
    q.head = nullptr;
    q.tail = nullptr;
}

void Push(Queue& q, char value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (IsEmpty(q)) {
        q.head = newNode;
        q.tail = newNode;
    }
    else {
        q.tail->next = newNode;
        q.tail = newNode;
    }

    q.size++;
}

void PopKElements(Queue& q, int k) {
    if (k <= 0 || IsEmpty(q)) return;

    while (q.head != nullptr && k > 0) {
        Node* temp = q.head;
        q.head = q.head->next;

        if (q.head == nullptr) {
            q.tail = nullptr;
        }

        delete temp;
        q.size--;
        k--;
    }
}

void AddAfterElement(Queue& q, char targetChar, char newValue) {
    if (IsEmpty(q)) {
        cout << "ќчередь пуста" << endl;
        return;
    }

    Queue tempQueue;
    InitializeQueue(tempQueue);

    bool elementFound = false;

    while (!IsEmpty(q)) {
        Node* current = q.head;
        Push(tempQueue, current->data);

        if (current->data == targetChar && !elementFound) {
            Push(tempQueue, newValue);
            elementFound = true;
        }

        PopKElements(q, 1);
    }

    while (!IsEmpty(tempQueue)) {
        Node* current = tempQueue.head;
        Push(q, current->data);
        PopKElements(tempQueue, 1);
    }

    if (!elementFound) {
        cout << "Ёлемент с символом '" << targetChar << "' не найден в очереди" << endl;
    }
}

void ShowQueue(const Queue& q) {
    Node* temp = q.head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Ru");

    Queue queue;
    InitializeQueue(queue);

    Push(queue, 'a');
    Push(queue, 'b');
    Push(queue, 'c');
    Push(queue, 'd');
    Push(queue, 'e');
    Push(queue, 'f');

    cout << "—одержимое очереди: ";
    ShowQueue(queue);

    int k = 2;
    PopKElements(queue, k);

    cout << "ќчередь после удалени€ " << k << " первых элементов: ";
    ShowQueue(queue);

    char targetChar = 'e';
    char newValue = 'x';
    AddAfterElement(queue, targetChar, newValue);

    cout << "ќчередь после добавлени€ '" << newValue << "' после '" << targetChar << "': ";
    ShowQueue(queue);

    return 0;
}