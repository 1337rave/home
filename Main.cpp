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
    explicit Node(T data, Node<T>* next = nullptr, Node<T>* prev = nullptr) {
        setData(data);
        setNext(next);
        setPrev(prev);
    }
    Node<T>* getNext() const {
        return next;
    }
    Node<T>* getPrev() const {
        return prev;
    }
    void setNext(Node<T>* next) {
        this->next = next;
    }
    void setPrev(Node<T>* prev) {
        this->prev = prev;
    }
    T getData() const {
        return data;
    }
    void setData(T data) {
        this->data = data;
    }
};

template<typename T>
class Array {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
    int capacity;
    int grow;
public:
    Array() : head(nullptr), tail(nullptr), size(0), capacity(0), grow(1) {}

    ~Array() {
        RemoveAll();
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int size, int grow = 1) {
        this->grow = grow;
        if (size < capacity) {
            while (this->size > size) {
                RemoveAt(this->size - 1);
            }
        }
        else if (size > capacity) {
            int extraSize = size - capacity;
            int newCapacity = capacity + (extraSize / grow + (extraSize % grow ? 1 : 0)) * grow;
            while (capacity < newCapacity) {
                Add(T());
            }
        }
    }

    int GetUpperBound() const {
        return capacity - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        while (size < capacity) {
            RemoveAt(capacity - 1);
        }
    }

    void RemoveAll() {
        while (head) {
            Node<T>* temp = head;
            head = head->getNext();
            delete temp;
        }
        tail = nullptr;
        size = 0;
        capacity = 0;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of bounds." << std::endl;
            exit(1);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->getNext();
        }
        return current->getData();
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of bounds." << std::endl;
            exit(1);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->getNext();
        }
        if (current->getPrev()) {
            current->getPrev()->setNext(current->getNext());
        }
        else {
            head = current->getNext();
        }
        if (current->getNext()) {
            current->getNext()->setPrev(current->getPrev());
        }
        else {
            tail = current->getPrev();
        }
        delete current;
        --size;
    }

    T GetAt(int index) const {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of bounds." << std::endl;
            exit(1);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->getNext();
        }
        return current->getData();
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of bounds." << std::endl;
            exit(1);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->getNext();
        }
        current->setData(value);
    }

    T operator[](int index) const {
        return GetAt(index);
    }

    void Add(const T& value) {
        if (size == capacity) {
            SetSize(size + grow);
        }
        Node<T>* newNode = new Node<T>(value, nullptr, tail);
        if (!head) {
            head = newNode;
        }
        else {
            tail->setNext(newNode);
        }
        tail = newNode;
        ++size;
    }

    void Append(const Array<T>& other) {
        for (int i = 0; i < other.size; ++i) {
            Add(other[i]);
        }
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this == &other) {
            return *this;
        }
        RemoveAll();
        Append(other);
        return *this;
    }

    T* GetData() const {
        T* data = new T[size];
        Node<T>* current = head;
        int index = 0;
        while (current) {
            data[index++] = current->getData();
            current = current->getNext();
        }
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            std::cerr << "Error: Index out of bounds." << std::endl;
            exit(1);
        }
        if (index == size) {
            Add(value);
            return;
        }
        if (size == capacity) {
            SetSize(size + grow);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->getNext();
        }
        Node<T>* newNode = new Node<T>(value, current, current->getPrev());
        if (current->getPrev()) {
            current->getPrev()->setNext(newNode);
        }
        else {
            head = newNode;
        }
        current->setPrev(newNode);
        ++size;
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Error: Index out of bounds." << std::endl;
            exit(1);
        }
        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->getNext();
        }
        if (current->getPrev()) {
            current->getPrev()->setNext(current->getNext());
        }
        else {
            head = current->getNext();
        }
        if (current->getNext()) {
            current->getNext()->setPrev(current->getPrev());
        }
        else {
            tail = current->getPrev();
        }
        delete current;
        --size;
    }
};

int main() {
    Array<int> arr;
    arr.SetSize(5, 5);
    for (int i = 0; i < 10; ++i) {
        arr.Add(i);
    }

    std::cout << "Array size: " << arr.GetSize() << std::endl;
    std::cout << "Array upper bound: " << arr.GetUpperBound() << std::endl;
    std::cout << "Array is empty: " << (arr.IsEmpty() ? "true" : "false") << std::endl;

    std::cout << "Array content: ";
    for (int i = 0; i < arr.GetSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    arr.RemoveAt(3);
    std::cout << "After removing element at index 3: ";
    for (int i = 0; i < arr.GetSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}   