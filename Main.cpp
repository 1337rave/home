#include <iostream>

template<typename T>
class Node {
private:
    Node<T>* next;
    T data;
    Node<T>* prev;
public:
    Node() {
        next = nullptr;
        prev = nullptr;
    }
    explicit Node(T data, Node<T>* next, Node<T>* prev) {
        setNext(next);
        setPrev(prev);
        setData(data);
    }
    Node<T>* getNext() const {
        return next;
    }
    Node<T>* getPrev() const {
        return prev;
    }
    void setNext(Node<T>* next) {
        if (next != nullptr) {
            this->next = next;
        }
    }
    void setPrev(Node<T>* prev) {
        if (prev != nullptr) {
            this->prev = prev;
        }
    }
    T getData() const {
        return data;
    }
    void setData(T data) {
        this->data = data;
    }
};

template<typename T>
class DoubleLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
public:
    DoubleLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DoubleLinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->getNext();
            delete temp;
        }
        tail = nullptr;
    }

    void AddToHead(const T& value) {
        Node<T>* newNode = new Node<T>(value, head, nullptr);
        if (!head) {
            tail = newNode;
        }
        else {
            head->setPrev(newNode);
        }
        head = newNode;
        size++;
    }

    void AddToTail(const T& value) {
        Node<T>* newNode = new Node<T>(value, nullptr, tail);
        if (!tail) {
            head = newNode;
        }
        else {
            tail->setNext(newNode);
        }
        tail = newNode;
        size++;
    }

    void Show() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->getData() << " ";
            current = current->getNext();
        }
        std::cout << std::endl;
    }

    // Додавання елемента в кінець черги
    void Enqueue(const T& value) {
        AddToTail(value);
    }

    // Видалення елемента з початку черги
    void Dequeue() {
        if (!head) {
            std::cerr << "Queue is empty\n";
            return;
        }
        Node<T>* temp = head;
        head = head->getNext();
        if (!head) {
            tail = nullptr;
        }
        else {
            head->setPrev(nullptr);
        }
        delete temp;
        size--;
    }
};

int main() {
    DoubleLinkedList<int> queue;

    // Додавання елементів в чергу
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);

    // Виведення черги перед видаленням
    std::cout << "Queue before dequeue: ";
    queue.Show(); // Outputs: 1 2 3

    // Видалення елемента з початку черги
    queue.Dequeue();

    // Виведення черги після видалення
    std::cout << "Queue after dequeue: ";
    queue.Show(); // Outputs: 2 3

    return 0;
}
