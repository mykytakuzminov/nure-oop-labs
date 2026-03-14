#include <iostream>
#include <stdexcept>

class Queue
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node(int val);
    };

    int size = 0;
    Node *head = nullptr;
    Node *tail = nullptr;

    void CheckHead() const;

public:
    Queue();
    Queue(int val);
    Queue(int arr[], int arrSize);
    Queue(const Queue &other);
    Queue(Queue &&other);
    ~Queue();

    Queue &operator=(const Queue &other);

    void Enqueue(int val);
    int Dequeue();
    int Peek() const;
    int GetAt(int index) const;
    bool IsEqual(const Queue &other) const;
    void Print() const;
};

Queue::Node::Node(int val)
{
    data = val;
    next = nullptr;
}

void Queue::CheckHead() const
{
    if (!head)
        throw std::runtime_error("Queue is empty!");
}

Queue::Queue() {}

Queue::Queue(int val)
{
    Enqueue(val);
}

Queue::Queue(int arr[], int arrSize)
{
    for (int i = 0; i < arrSize; i++)
        Enqueue(arr[i]);
}

Queue::Queue(const Queue &other)
{
    Node *temp = other.head;
    while (temp)
    {
        Enqueue(temp->data);
        temp = temp->next;
    }
}

Queue::Queue(Queue &&other)
{
    head = other.head;
    tail = other.tail;
    size = other.size;

    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

Queue::~Queue()
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

Queue &Queue::operator=(const Queue &other)
{
    if (this == &other)
        return *this;

    while (head)
        Dequeue();

    Node *temp = other.head;
    while (temp)
    {
        Enqueue(temp->data);
        temp = temp->next;
    }

    return *this;
}

void Queue::Enqueue(int val)
{
    Node *node = new Node(val);

    if (!head && !tail)
    {
        head = node;
        tail = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }

    size += 1;
}

int Queue::Dequeue()
{
    CheckHead();

    Node *temp = head;
    int val = head->data;

    head = head->next;
    if (!head)
        tail = nullptr;

    size -= 1;

    delete temp;
    return val;
}

int Queue::Peek() const
{
    CheckHead();
    return head->data;
}

int Queue::GetAt(int index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of bounds!");
    }

    Node *temp = head;
    for (int i = 0; i < index; i++)
        temp = temp->next;
    return temp->data;
}

bool Queue::IsEqual(const Queue &other) const
{
    if (size != other.size)
        return false;

    Node *temp1 = head;
    Node *temp2 = other.head;

    for (int i = 0; i < size; i++)
    {
        if (GetAt(i) != other.GetAt(i))
            return false;
    }

    return true;
}

void Queue::Print() const
{
    if (!head)
    {
        std::cout << "Queue is empty." << std::endl;
        return;
    }

    Node *temp = head;
    while (temp)
    {
        std::cout << temp->data << " -> ";
        temp = temp->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main()
{
    try
    {
        Queue q1;
        std::cout << "Queue 1 (empty): ";
        q1.Print();

        Queue q2(5);
        std::cout << "Queue 2 (with initial value): ";
        q2.Print();

        int arr[] = {5, 2, 0, 8, 4, 2};
        int arrSize = 6;

        Queue q3(arr, arrSize);
        std::cout << "Queue 3 (from array): ";
        q3.Print();

        Queue q4(q3);
        Queue q5 = q3;
        std::cout << "Queue 4 (copy init): ";
        q4.Print();
        std::cout << "Queue 4 (copy init with operator): ";
        q5.Print();

        Queue q6 = Queue(10);
        std::cout << "Queue 6 (move init): ";
        q6.Print();

        q1.Enqueue(1);
        q1.Enqueue(2);
        q1.Enqueue(3);
        std::cout << "Enqueue some values to q1: ";
        q1.Print();

        q1.Dequeue();
        std::cout << "Dequeue value from q1: ";
        q1.Print();

        std::cout << "Peek value from q1 without removing it: " << q1.Peek();
        std::cout << "\nGet value at index 1: " << q1.GetAt(1);
        std::cout << "\nq1 (to check): ";
        q1.Print();

        std::cout << "nq1 is equal q3 (0 - false, 1 - true): " << q1.IsEqual(q3);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
