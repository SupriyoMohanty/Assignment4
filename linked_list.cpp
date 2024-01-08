// Implement Queue using linked list. 
// But, a linked list can have maximum 5 elements, so if the user pushes sixth element then 
// you should create one more linked list and push the newer element into that linked list.

// For the outside user, your program should have only two functions:
//   1. push()
//   2. pop()


#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class Queue {
private:
    int max_size;
    Node* front;
    Node* rear;
    int size;
    Queue* next_queue;

public:
    Queue(int maxSize = 5) : max_size(maxSize), front(nullptr), rear(nullptr), size(0), next_queue(nullptr) {
        cout << "----------------New Queue Started---------------" << endl;
    }

    bool is_empty() {
        return front == nullptr;
    }

    bool is_full() {
        return size == max_size;
    }

    void enqueue(int data) {
        if (is_full()) {
            if (next_queue == nullptr) {
                next_queue = new Queue(max_size); //assigning next_queue with max size 
            }
            next_queue->enqueue(data);
            return;
        }

        Node* new_node = new Node(data);
        if (is_empty()) {
            front = rear = new_node;
        } else {
            rear->next = new_node;
            rear = new_node;
        }
        size++;
    }

    int dequeue() {
        if (is_empty()) {
            if (next_queue != nullptr) {
                int dequeuedValue = next_queue->dequeue();
                return dequeuedValue;
            } else {
                cout << "Queue is empty" << endl;
                return -1; // Assuming -1 as an indicator of an empty queue
            }
        }

        int frontData = front->data;
        Node* temp = front;
        front = front->next;
        delete temp;
        size--;

        if (front == nullptr) {
            rear = nullptr;
        }

        return frontData;
    }

    void display() {
        Queue* currentQueue = this;

        while (currentQueue != nullptr) {
            Node* current = currentQueue->front;
            while (current) {
                cout << current->data << " ";
                current = current->next;
            }
            cout << endl;

            currentQueue = currentQueue->next_queue;
        }
    }

    ~Queue() {
        Node* current = front;
        Node* nextNode;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }

        if (next_queue != nullptr) {
            delete next_queue;
        }
    }
};

int main() {
    Queue mainQueue;

    while (true) {
        cout << "\n1. Enqueue";
        cout << "\n2. Dequeue";
        cout << "\n3. Display";
        cout << "\n4. Quit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int value;
                cout << "Enter the value to enqueue: ";
                cin >> value;
                mainQueue.enqueue(value);
                cout << value << " enqueued to the queue." << endl;
                break;
            }
            case 2: {
                int dequeuedValue = mainQueue.dequeue();
                if (dequeuedValue != -1) {
                    cout << dequeuedValue << " dequeued from the queue." << endl;
                }
                break;
            }
            case 3:
                cout << "Current Queues:" << endl;
                mainQueue.display();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}
