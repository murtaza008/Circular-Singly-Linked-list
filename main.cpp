#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;

    // Constructor to create a new node
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Circular Singly Linked List class
class CircularSinglyLinkedList {
private:
    Node* head;

public:
    // Constructor to initialize the head of the list
    CircularSinglyLinkedList() {
        head = nullptr;
    }

    // Function to add a node at the end of the list
    void append(int value) {
        Node* newNode = new Node(value);

        // If the list is empty
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; // Points to itself to make it circular
        } else {
            Node* temp = head;
            // Traverse the list to find the last node
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head; // Connect last node back to head
        }
    }

    // Function to delete a node by value
    void deleteByValue(int value) {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        // If the node to be deleted is the head
        if (head->data == value) {
            if (head->next == head) { // Only one node in the list
                delete head;
                head = nullptr;
            } else {
                // Find the last node to update its next pointer
                while (temp->next != head) {
                    temp = temp->next;
                }
                temp->next = head->next;
                delete head;
                head = temp->next; // Move head to next node
            }
            return;
        }

        // Search for the node to delete
        do {
            prev = temp;
            temp = temp->next;
            if (temp->data == value) {
                prev->next = temp->next;
                delete temp;
                return;
            }
        } while (temp != head);

        cout << "Value not found." << endl;
    }

    // Function to display the list
    void display() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        Node* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(head)" << endl; // Indicating circular nature
    }

    // Function to search for a value in the list
    bool search(int value) {
        if (head == nullptr) {
            return false;
        }
        Node* temp = head;
        do {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
        } while (temp != head);
        return false;
    }

    // Destructor to clean up memory
    ~CircularSinglyLinkedList() {
        if (head == nullptr) {
            return;
        }
        Node* temp = head;
        do {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);
        head = nullptr;
    }
};

// Main function to test the list
int main() {
    CircularSinglyLinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);

    cout << "Original List: ";
    list.display();

    cout << "Searching for 20: " << (list.search(20) ? "Found" : "Not Found") << endl;

    list.deleteByValue(20);
    cout << "List after deleting 20: ";
    list.display();

    return 0;
}
