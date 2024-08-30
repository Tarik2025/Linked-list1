#include <iostream>

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Insert at the head, tail, or a specific index
    void insert(int val, std::string pos, int idx = -1) {
        Node* newNode = new Node(val);

        if (pos == "head") {
            newNode->next = head;
            head = newNode;
            if (!tail) {
                tail = newNode;
            }
        } else if (pos == "tail") {
            if (!tail) {
                head = tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        } else if (pos == "index" && idx >= 0) {
            if (idx == 0) {
                insert(val, "head");
                return;
            }
            Node* temp = head;
            for (int i = 0; i < idx - 1 && temp != nullptr; ++i) {
                temp = temp->next;
            }
            if (temp != nullptr) {
                newNode->next = temp->next;
                temp->next = newNode;
                if (newNode->next == nullptr) {
                    tail = newNode;
                }
            } else {
                std::cout << "Index out of bounds." << std::endl;
                delete newNode;
                return;
            }
        } else {
            std::cout << "Invalid position specified." << std::endl;
            delete newNode;
            return;
        }

        size++;
    }

    // Delete from the head, tail, or a specific index
    void remove(std::string pos, int idx = -1) {
        if (!head) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        if (pos == "head") {
            Node* temp = head;
            head = head->next;
            delete temp;
            if (!head) {
                tail = nullptr;
            }
        } else if (pos == "tail") {
            if (head == tail) {
                delete head;
                head = tail = nullptr;
            } else {
                Node* temp = head;
                while (temp->next != tail) {
                    temp = temp->next;
                }
                delete tail;
                tail = temp;
                tail->next = nullptr;
            }
        } else if (pos == "index" && idx >= 0) {
            if (idx == 0) {
                remove("head");
                return;
            }
            Node* temp = head;
            for (int i = 0; i < idx - 1 && temp != nullptr; ++i) {
                temp = temp->next;
            }
            if (temp != nullptr && temp->next != nullptr) {
                Node* nodeToDelete = temp->next;
                temp->next = temp->next->next;
                if (nodeToDelete == tail) {
                    tail = temp;
                }
                delete nodeToDelete;
            } else {
                std::cout << "Index out of bounds." << std::endl;
                return;
            }
        } else {
            std::cout << "Invalid position specified." << std::endl;
            return;
        }

        size--;
    }

    // Get value at a specific index
    int get(int idx) {
        if (idx < 0 || idx >= size) {
            std::cout << "Index out of bounds." << std::endl;
            return -1;
        }

        Node* temp = head;
        for (int i = 0; i < idx; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    // Display all elements in the linked list
    void display() {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Destructor to clean up memory
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    LinkedList list;
    list.insert(1, "head"); // Insert 1 at the head
    list.insert(2, "tail"); // Insert 2 at the tail
    list.insert(3, "tail"); // Insert 3 at the tail
    list.insert(4, "index", 1); // Insert 4 at index 1

    list.display(); // Output: 1 4 2 3

    std::cout << "Value at index 2: " << list.get(2) << std::endl; // Output: 2

    list.remove("head"); // Remove head
    list.display(); // Output: 4 2 3

    list.remove("tail"); // Remove tail
    list.display(); // Output: 4 2

    list.remove("index", 0); // Remove at index 0
    list.display(); // Output: 2

    return 0;
}
