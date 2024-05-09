#include <iostream>
using namespace std;

template <typename T>
class Node 
{
public:
    T data;
    Node* prev;
    Node* next;

    Node(const T& data) : data(data), prev(nullptr), next(nullptr) {}
};
template <typename T>
class List
{
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    List(const initializer_list<T>& initList) : List() 
    {
        for (const auto& item : initList)
        {
            append(item);
        }
    }
    ~List() {
        while (head)
        {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void append(const T& data) 
    {
        Node<T>* newNode = new Node<T>(data);
        if (!head) 
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    void insert(int index, const T& data) 
    {
        if (index < 0 || index > size)
        {
            cerr << "Index out of range" << endl;
        }
        if (index == size) 
        {
            append(data);
        }

        Node<T>* newNode = new Node<T>(data);
        if (index == 0)
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        else 
        {
            Node<T>* current = getNode(index);
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }
        size++;
    }
    Node<T>* getNode(int index) 
    {
        if (index < 0 || index >= size) 
        {
            cerr << "Index out of range" << endl;
            return nullptr;
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) 
        {
            current = current->next;
        }
        return current;
    }
    T& operator[](int index) 
    {
        return getNode(index)->data;
    }
    void deleteByValue(const T& value)
    {
        Node<T>* current = head;
        while (current)
        {
            if (current->data == value)
            {
                if (current == head) 
                {
                    head = head->next;
                    if (head) 
                    {
                        head->prev = nullptr;
                    }
                }
                else if (current == tail)
                {
                    tail = tail->prev;
                    tail->next = nullptr;
                }
                else
                {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;
                size--;
                return;
            }
            current = current->next;
        }
    }
    void removeDuplicates() 
    {
        Node<T>* current = head;
        while (current)
        {
            Node<T>* runner = current->next;
            while (runner)
            {
                if (runner->data == current->data) 
                {
                    Node<T>* temp = runner;
                    runner->prev->next = runner->next;
                    if (runner->next)
                    {
                        runner->next->prev = runner->prev;
                    }
                    runner = runner->next;
                    delete temp;
                    size--;
                }
                else 
                {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }
    T findMax() 
    {
        if (!head)
        {
            cerr << "List is empty" << endl;
            throw exception();
        }
        T maxVal = head->data;
        Node<T>* current = head->next;
        while (current)
        {
            if (current->data > maxVal) 
            {
                maxVal = current->data;
            }
            current = current->next;
        }
        return maxVal;
    }
    T findMin()
    {
        if (!head)
        {
            cerr << "List is empty" << endl;
            throw exception();
        }
        T minVal = head->data;
        Node<T>* current = head->next;
        while (current)
        {
            if (current->data < minVal) 
            {
                minVal = current->data;
            }
            current = current->next;
        }
        return minVal;
    }
    void reversePrint() 
    {
        Node<T>* current = tail;
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
    int getSize() 
    {
        return size;
    }
};

int main() {
    List<int> myList = { 1, 2, 3, 4, 5 };
    myList.insert(2, 10);
    myList[3] = 88;
    myList.deleteByValue(3);
    myList.removeDuplicates();
    cout << "Max value : " << myList.findMax() << endl;
    cout << "Min value : " << myList.findMin() << endl;
    cout << "Size of list : " << myList.getSize() << endl;
    myList.reversePrint();
}
