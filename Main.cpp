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

    DoubleLinkedList<T>* Clone() const {
        DoubleLinkedList<T>* clonedList = new DoubleLinkedList<T>();
        Node<T>* current = head;
        while (current) {
            clonedList->AddToTail(current->getData());
            current = current->getNext();
        }
        return clonedList;
    }

    DoubleLinkedList<T> operator*(const DoubleLinkedList<T>& other) const {
        DoubleLinkedList<T> commonElementsList;
        Node<T>* current = head;
        while (current) {
            Node<T>* otherCurrent = other.head;
            while (otherCurrent) {
                if (current->getData() == otherCurrent->getData()) {
                    commonElementsList.AddToTail(current->getData());
                    break;
                }
                otherCurrent = otherCurrent->getNext();
            }
            current = current->getNext();
        }
        return commonElementsList;
    }

    void Print() const {
        Node<T>* current = head;
        while (current) {
            std::cout << current->getData() << " ";
            current = current->getNext();
        }
        std::cout << std::endl;
    }
};

int main() {
    DoubleLinkedList<int> list1;
    list1.AddToTail(1);
    list1.AddToTail(2);
    list1.AddToTail(3);

    DoubleLinkedList<int> list2;
    list2.AddToTail(2);
    list2.AddToTail(3);
    list2.AddToTail(4);

    DoubleLinkedList<int> commonElementsList = list1 * list2;
    std::cout << "Common Elements List: ";
    commonElementsList.Print();

    return 0;
}
