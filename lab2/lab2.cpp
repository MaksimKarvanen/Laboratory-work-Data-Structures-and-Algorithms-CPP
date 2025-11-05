#include <iostream>
#define MAX_SIZE 100

using namespace std;

class Stack
{
    private:
        int top;
        int data[MAX_SIZE];

    public:
        Stack() { top=-1; }

        void push(int item)
        {
            if (top >= MAX_SIZE - 1)
            {
                cout<<"Stack Overflow"<<endl;
                return;
            }

            data[++top] = item;
        }

        int pop()
        {
            if (top < 0)
            {
                cout<<"Stack is empty"<<endl;
                return 0;
            }
            return data[top--];
        }

        int peek()
        {
            if (top < 0)
            {
                cout<<"Stack is empty"<<endl;
                return 0;
            }
            return data[top];
        }

        bool empty()
        {
            return (top < 0);
        }

        int size()
        {
            return top + 1;
        }

        void display()
        {
            if (empty())
            {
                cout<<"Stack is empty"<<endl;
                return;
            }

            for (int i = top; i >= 0; i--)
            {
                cout<<data[i]<<" ";
            }
            cout<<endl;
        }

        int search(int item)
        {
            for (int i = top; i >= 0; i--)
            {
                if (data[i] == item)
                {
                    return top - i;
                }
            }
            return -1;
        }

        Stack copyStack()
        {
            Stack newStack;
            newStack.top = this->top;
            for (int i = 0; i <= top; i++)
            {
                newStack.data[i] = this->data[i];
            }
            return newStack;
        }
};

class Deque
{
    private:
        int head;
        int tail;
        int data[MAX_SIZE];

    public:
        Deque(): head(-1), tail(-1) {}

        bool empty()
        {
            return (head == -1 && tail == -1);
        }

        bool full()
        {
            return tail == MAX_SIZE - 1;
        }

        int front()
        {
            if (empty())
            {
                cout<<"Empty Queue"<<endl;
                return -1;
            }
            return data[head];
        }

        int back()
        {
            if (empty())
            {
                cout<<"Empty Queue"<<endl;
                return -1;
            }
            return data[tail];
        }

        void push_back(int item)
        {
            if (full())
            {
                cout << "Full Queue"<<endl;
                return;
            }
            if (empty())
            {
                head = 0;
            }
            tail++;
            data[tail] = item;
        }

        void push_front(int item)
        {
            if (full())
            {
                cout << "Full Queue"<<endl;
                return;
            }

            if (empty())
            {
                head = 0;
                tail = 0;
            }
            else if (head > 0)
            {
                head--;
            }
            else
            {
                for (int i = tail; i >= head; i--)
                {
                    data[i + 1] = data[i];
                }
                tail++;
            }
            data[head] = item;
        }

        int pop_front()
        {
            if (empty())
            {
                cout << "Empty Queue"<<endl;
                return -1;
            }
            int temp = data[head];
            head++;

            if (empty())
            {
                head = tail = -1;
            }
            return temp;
        }

        int pop_back()
        {
            if (empty())
            {
                cout<<"Empty Queue"<<endl;
                return -1;
            }
            int temp = data[tail];
            tail--;

            if (empty())
            {
                head = tail = -1;
            }
            return temp;
        }

        int size()
        {
            if (empty())
            {
                return 0;
            }
            return tail - head + 1;
        }

        void clear()
        {
            head = -1;
            tail = -1;
        }

        void display()
        {
            if (empty())
            {
                cout<<"Empty Queue"<<endl;
                return;
            }
            for (int i = head; i <= tail; i++)
            {
                cout<<data[i]<<" ";
            }
            cout<<endl;
        }

        void insert(int item, int pos)
        {
            if (full())
            {
                cout << "Full Queue"<<endl;
                return;
            }

            if (pos < 0 || pos >= size())
            {
                cout << "Pos out of Queue"<<endl;
                return;
            }

            if (empty() || pos == size())
            {
                push_back(item);
                return;
            }

            if (pos == 0)
            {
                push_front(item);
                return;
            }

             for (int i = tail; i >= head + pos; i--)
             {
                 data[i + 1] = data[i];
             }

            data[head + pos] = item;
            tail++;
        }

        void erase(int pos)
        {
            if (empty())
            {
                cout << "Empty Queue"<<endl;
                return;
            }

            if (pos < 0 || pos >= size())
            {
                cout << "Pos out of Queue"<<endl;
                return;
            }

            if (pos == 0)
            {
                pop_front();
                return;
            }

            if (pos == size() - 1)
            {
                pop_back();
                return;
            }

            for (int i = head + pos; i < tail; i++)
            {
                data[i] = data[i + 1];
            }

            tail--;
            if (head > tail)
            {
                head = tail = -1;
            }
        }
};

class Queue
{
    private:
        Deque deque;

    public:
        void push(int item)
        {
            deque.push_back(item);
        }

        int pop()
        {
            return deque.pop_front();
        }

        int front()
        {
            return deque.front();
        }

        int back()
        {
            return deque.back();
        }

        bool empty()
        {
            return deque.empty();
        }

        bool full()
        {
            return deque.full();
        }

        int size()
        {
            return deque.size();
        }

        void clear()
        {
            return deque.clear();
        }

        void display()
        {
            deque.display();
        }

        void insert(int item, int pos)
        {
            deque.insert(item, pos);
        }

        void erase(int pos)
        {
            deque.erase(pos);
        }
};

class Node
{
    public:
        int data;
        Node *prev;
        Node *next;

        Node()
        {
            data = 0;
            next = nullptr;
            prev = nullptr;
        }

        Node(int data): data(data), prev(nullptr), next(nullptr) {}
};

class LinkedList
{
    Node *head;
    int size;

    public:
        LinkedList()
        {
            head = nullptr;
            size = 0;
        }

        void display()
        {
            Node *temp = head;
            if (head == nullptr)
            {
                cout<<"Empty List"<<endl;
            }

            while (temp != nullptr)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }

        void push_back(int item)
        {
            Node *newNode = new Node(item);
            size++;

            if (head == nullptr)
            {
                head = newNode;
                return;
            }

            Node *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        void push_front(int item)
        {
            Node *newNode = new Node(item);
            size++;

            if (head == nullptr)
            {
                head = newNode;
                return;
            }

            newNode->next = head;
            head = newNode;
        }

        int pop_front()
        {
            if (head == nullptr)
            {
                cout<<"Empty List"<<endl;
                return -1;
            }

            Node *temp = head;
            head = head->next;
            int data = temp->data;
            delete temp;
            size--;
            return data;
        }

        int pop_back()
        {
            if (head == nullptr)
            {
                cout<<"Empty List"<<endl;
                return -1;
            }

            if (head->next == nullptr)
            {
                int data = head->data;
                delete head;
                head = nullptr;
                size--;
                return data;
            }

            Node *temp = head;
            while (temp->next->next != nullptr)
            {
                temp = temp->next;
            }
            int data = temp->data;
            delete temp->next;
            temp->next = nullptr;
            size--;
            return data;
        }

        int listSize()
        {
            return size;
        }

        void insert(int item, int pos)
        {
            if (pos < 0 || pos > listSize())
            {
                cout<<"Pos out of List"<<endl;
                return;
            }

            if (pos == 0)
            {
                push_front(item);
                return;
            }

            if (pos == listSize())
            {
                push_back(item);
                return;
            }

            Node *newNode = new Node(item);
            Node *temp = head;
            for (int i = 0; i < pos - 1; i++)
            {
                temp = temp->next;
            }

            newNode->next = temp->next;
            temp->next = newNode;
            size++;
        }

        void erase(int pos)
        {
            if (pos < 0 || pos > listSize())
            {
                cout<<"Pos out of List"<<endl;
                return;
            }

            if (pos == 0)
            {
                pop_front();
                return;
            }

            if (pos == listSize() - 1)
            {
                pop_back();
                return;
            }

            Node *temp = head;
            Node *prev = nullptr;

            for (int i = 0; i < pos; i++)
            {
                prev = temp;
                temp = temp->next;
            }

            prev->next = temp->next;
            delete temp;
            size--;
        }
};

class DoubleLinkedList
{
    Node *head;
    Node *tail;
    int size;

    public:
        DoubleLinkedList()
        {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        void display()
        {
                Node *temp = head;
                if (head == nullptr)
                {
                    cout<<"Empty List"<<endl;
                    return;
                }
                while (temp != nullptr)
                {
                    cout << temp->data << " ";
                    temp = temp->next;
                }
                cout << endl;}

        void push_back(int item)
        {
            Node *newNode = new Node(item);
            size++;

            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
                return;
            }

            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        void push_front(int item)
        {
            Node *newNode = new Node(item);
            size++;

            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
                return;
            }

            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        int pop_front()
        {
            if (head == nullptr)
            {
                cout<<"Empty List"<<endl;
                return -1;
            }

            Node *temp = head;
            head = head->next;

            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }

            int data = temp->data;
            delete temp;
            size--;
            return data;
        }

        int pop_back()
        {
            if (head == nullptr)
            {
                cout<<"Empty List"<<endl;
                return -1;
            }

            Node *temp = tail;
            tail = tail->prev;

            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }

            int data = temp->data;
            delete temp;
            size--;
            return data;
        }

        int listSize()
        {
            return size;
        }

        void insert(int item, int pos)
        {
            if (pos < 0 || pos > listSize())
            {
                cout<<"Pos out of List"<<endl;
                return;
            }

            if (pos == 0)
            {
                push_front(item);
                return;
            }

            if (pos == listSize())
            {
                push_back(item);
                return;
            }

            Node *newNode = new Node(item);
            Node *temp;

            if (pos < listSize() / 2)
            {
                temp = head;
                for (int i = 0; i < pos; i++)
                {
                    temp = temp->next;
                }
            }
            else
            {
                temp = tail;
                for (int i = listSize() - 1; i > pos; i--)
                {
                    temp = temp->prev;
                }
            }

            newNode->prev = temp->prev;
            newNode->next = temp;
            temp->prev->next = newNode;
            temp->prev = newNode;
            size++;
        }

        void erase(int pos)
        {
            if (pos < 0 || pos >= listSize())
            {
                cout << "Pos out of List" << endl;
                return;
            }

            if (pos == 0)
            {
                pop_front();
                return;
            }

            if (pos == listSize() - 1)
            {
                pop_back();
                return;
            }

            Node *temp;

            if (pos < listSize() / 2)
            {
                temp = head;
                for (int i = 0; i < pos; i++)
                {
                    temp = temp->next;
                }
            }
            else
            {
                temp = tail;
                for (int i = listSize() - 1; i > pos; i--)
                {
                    temp = temp->prev;
                }
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            size--;
        }
};

struct BSTNode
{
    int data;
    BSTNode *left;
    BSTNode *right;
};

BSTNode* createNode(int data)
{
    BSTNode* newNode = new BSTNode();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

BSTNode* insertNode(BSTNode* node, int data)
{
    if (node == nullptr)
    {
        return createNode(data);
    }

    if (data < node->data)
    {
        node->left = insertNode(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insertNode(node->right, data);
    }
    return node;
}

void inorderTraversal(BSTNode* node)
{
    if (node != nullptr)
    {
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

BSTNode* searchNode(BSTNode* node, int key)
{
    if (node == nullptr || node->data == key)
    {
        return node;
    }

    if (node->data < key)
    {
        return searchNode(node->right, key);
    }

    return searchNode(node->left, key);
}

BSTNode* minValueNode(BSTNode* node)
{
    BSTNode* current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

BSTNode* deleteNode(BSTNode* node, int data)
{
    if (node == nullptr)
    {
        return node;
    }

    if (data < node->data)
    {
        node->left = deleteNode(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = deleteNode(node->right, data);
    }
    else
    {
        if (node->left == nullptr)
        {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr)
        {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }
        BSTNode* temp = minValueNode(node->right);

        node->data = temp->data;
        node->right = deleteNode(node->right, temp->data);
    }
    return node;
}

int main()
{
    // Cтек
    Stack s;
    cout << "Пустота стека (bool): " << s.empty() << endl;
    s.push(1);
    s.push(3);
    s.push(2);
    s.push(-1);
    s.push(-2);

    cout << "Размер стека: " << s.size() << endl;
    cout << "Верхний элемент: " << s.peek() << endl;
    s.pop();
    cout << "Размер стека: " << s.size() << endl;
    cout << "Верхний элемент: " << s.peek() << endl;
    cout << "Пустота стека (bool): " << s.empty() << endl;
    s.display();
    cout << "Элемент 3 находится с индексом: " << s.search(3) << endl;
    Stack s2 = s.copyStack();
    s2.display();

    cout << endl;

    // Дек
    Deque d;
    cout << "Пустота дэка (bool): " << d.empty() << endl;
    cout << "Полнота дэка (bool): " << d.full() << endl;
    d.push_back(1);
    d.push_back(3);
    d.display();
    d.push_front(-2);
    d.push_front(4);
    d.display();
    cout << "Длина дэка: " << d.size() << endl;
    cout << "Первый элемент: " << d.front() << endl;
    cout << "Последний элемент: " << d.back() << endl;
    d.pop_back();
    d.display();
    d.pop_front();
    d.display();
    cout << "Пустота дэка (bool): " << d.empty() << endl;
    cout << "Полнота дэка (bool): " << d.full() << endl;
    d.clear();
    d.display();
    d.push_back(1);
    d.push_back(3);
    d.push_back(-2);
    d.display();
    d.insert(10, 1);
    d.display();
    d.erase(2);
    d.display();

    cout << endl;

    //Очередь
    Queue q;
    cout << "Пустота очереди (bool): " << q.empty() << endl;
    cout << "Полнота очереди (bool): " << q.full() << endl;
    q.push(2);
    q.push(4);
    q.push(1);
    q.display();
    cout << "Длина очереди: " << q.size() << endl;
    cout << "Первый элемент: " << q.front() << endl;
    cout << "Последний элемент: " << q.back() << endl;
    cout << "Пустота очереди (bool): " << q.empty() << endl;
    q.pop();
    q.display();
    q.pop();
    q.display();
    q.clear();
    cout << "Пустота очереди (bool): " << q.empty() << endl;
    q.push(3);
    q.push(5);
    q.push(7);
    q.display();
    q.insert(32, 1);
    q.display();
    q.erase(0);
    q.display();

    cout << endl;

    // Односвязный список
    LinkedList ls;
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    cout << "Размер односвязного списка: " << ls.listSize() << endl;
    ls.display();
    cout << ls.pop_front() << endl;
    ls.display();
    cout << ls.pop_back() << endl;
    ls.display();
    ls.push_back(10);
    ls.push_back(12);
    ls.display();
    ls.insert(32, 1);
    ls.display();
    ls.erase(2);
    ls.display();

    cout << endl;

    // Двусвязный список
    DoubleLinkedList dls;
    dls.push_front(3);
    dls.push_front(4);
    dls.push_front(5);
    dls.display();
    dls.push_back(2);
    dls.push_back(1);
    dls.display();
    cout << dls.pop_front() << endl;
    cout << dls.pop_back() << endl;
    dls.display();
    cout << "Размер двусвязного списка: " << dls.listSize() << endl;
    dls.insert(32, 1);
    dls.display();
    dls.erase(2);
    dls.display();

    cout << endl;

    // Бинарное дерево поиска
    BSTNode* node = nullptr;
    node = insertNode(node, 50);
    node = insertNode(node, 30);
    node = insertNode(node, 20);
    node = insertNode(node, 80);
    node = insertNode(node, 60);
    node = insertNode(node, 70);

    cout << "Inorder traversal: ";
    inorderTraversal(node);
    cout << endl;

    node = deleteNode(node, 30);
    inorderTraversal(node);
    cout << endl;

    node = insertNode(node, 55);
    inorderTraversal(node);
    cout << endl;

    BSTNode* found = searchNode(node, 55);
    if (found != nullptr)
    {
        cout << "Узел найден в BST" << endl;
    }
    else
    {
        cout << "Узел не найден в BST" << endl;
    }

    return 0;
}