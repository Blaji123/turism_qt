//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_MYLIST_H
#define TURISM_QT_MYLIST_H

template<typename T>
class Lista{
private:
    struct Node{
        T data;
        Node* next;

        explicit Node(const T& data) : data(data), next(nullptr){}
    };

    Node* head;

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
public:
    Lista() : head(nullptr){}

    // Copy constructor
    Lista(const Lista& other) : head(nullptr) {
        Node* otherCurrent = other.head;
        Node* last = nullptr;
        while (otherCurrent) {
            Node* newNode = new Node(otherCurrent->data);
            if (!head) {
                head = newNode;
            } else {
                last->next = newNode;
            }
            last = newNode;
            otherCurrent = otherCurrent->next;
        }
    }

    // Copy assignment operator
    Lista& operator=(const Lista& other) {
        if (this != &other) {
            Lista temp(other);
            std::swap(head, temp.head);
        }
        return *this;
    }

    // Move constructor
    Lista(Lista&& other) noexcept : head(other.head) {
        other.head = nullptr;
    }

    // Move assignment operator
    Lista& operator=(Lista&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            other.head = nullptr;
        }
        return *this;
    }

    ~Lista(){
        clear();
    }

    void push_back(const T& value){
        if(!head){
            head = new Node(value);
        }else{
            Node* current = head;
            while(current->next){
                current = current->next;
            }
            current->next = new Node(value);
        }
    }

    [[nodiscard]] int size() const {
        Node* current = head;
        int cnt = 1;
        while(current->next){
            cnt++;
            current = current->next;
        }
        return cnt;
    }

    class Iterator : public std::iterator<std::forward_iterator_tag, T> {
    private:
        Node* current;

    public:
        explicit Iterator(Node* ptr) : current(ptr) {}

        // Overload operators to support iterator functionality
        T& operator*() const { return current->data; }
        Iterator& operator++() { current = current->next; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        bool operator==(const Iterator& other) const { return current == other.current; } // Add equality operator
        Iterator operator+(int n) const {
            Iterator it = *this;
            for (int i = 0; i < n; ++i)
                ++it;
            return it;
        }
        friend class Lista;
    };



    Iterator begin() const { return Iterator(head); }
    Iterator end() const {
        // Return an iterator to the element after the last valid one
        return Iterator(nullptr);
    }
    void erase(Iterator& it) {
        if (head == nullptr || it.current == nullptr)
            return; // Cannot erase from an empty list or a null iterator
        if (it.current == head) {
            head = head->next;
            delete it.current;
            it = Iterator(head);
        } else {
            Node* temp = head;
            while (temp->next && temp->next != it.current) {
                temp = temp->next;
            }
            if (temp->next) {
                temp->next = it.current->next;
                delete it.current;
                it = Iterator(temp->next);
            }
        }
    }
    T& at(long long index) const {
        int currentIndex = 0;
        Node* current = head;

        // Traverse the list until the desired position is reached
        while (current != nullptr && currentIndex < index) {
            current = current->next;
            ++currentIndex;
        }

        // If index is out of range, throw an exception
        if (current == nullptr) {
            throw std::out_of_range("Index out of range");
        }

        return current->data;
    }
    bool empty(){
        return head==nullptr;
    }
    T& operator[](int index) const {
        int currentIndex = 0;
        Node* current = head;

        // Traverse the list until the desired position is reached
        while (current != nullptr && currentIndex < index) {
            current = current->next;
            ++currentIndex;
        }

        // If index is out of range, throw an exception
        if (current == nullptr) {
            throw std::out_of_range("index out of range");
        }

        return current->data;
    }
};

#endif //TURISM_QT_MYLIST_H
