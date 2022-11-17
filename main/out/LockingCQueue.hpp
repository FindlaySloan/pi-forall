//////////////////////////////////////////////////////
// This code is adapted from the previous pracitcal //
//////////////////////////////////////////////////////

#include <mutex>
#include "Semaphore.hpp"

#ifndef SRC_LOCKING_CQUEUE_HPP
#define SRC_LOCKING_CQUEUE_HPP

template <typename T>
class QNode {
    public:
        QNode(T payload) {
            this->payload = payload;
            this->next = NULL;
        }
        QNode() {
            this->next = NULL;
        }
        T payload;
        QNode<T>* next;
};


template <typename T>
class LockingCQueue{
    private:
        QNode<T> *front;
        QNode<T> *rear;
        std::mutex enqMutex;
        std::mutex deqMutex;
        Semaphore *sem;
    public:
        LockingCQueue();
        ~LockingCQueue();
        void enqueue(T payload);
        T dequeue();

};

template <typename T>
LockingCQueue<T>::LockingCQueue() {
    // Creating the dummy node
    auto node = new QNode<T>();

    // Initting the to be not shared among processes (so only threads from this process can have access to it), and with initial value of 0 (as queue empty)
    sem = new Semaphore(0, 0);

    // Setting the dummy node to be the at the front and rear of the queue
    this->front = node;
    this->rear = node;
}

template <typename T>
LockingCQueue<T>::~LockingCQueue() {
    // Getting the front of the queue
    QNode<T> *front = this->front;

    // Loop through the queue and deleting each of the objects 
    while (front != NULL) {
        QNode<T> *temp;
        temp = front;
        front = front->next;
        delete temp;
    }
}

template <typename T>
void LockingCQueue<T>::enqueue(T payload) {
    // Creating the node to insert
    QNode<T> *node = new QNode<T>(payload);   

    // Aquiring the lock
    std::lock_guard<std::mutex> lock(this->enqMutex);

    // Setting the current last nodes next pointer to be the newly created node
    this->rear->next = node;

    // Setting the rear pointer to now point to the newly created node as it should be placed at the end of the queue
    this->rear = node;

    // Incrementing the semaphore as a new element has been added
    sem->post();
}

template <typename T>
T LockingCQueue<T>::dequeue() {
    T payload;

    // Waiting on the semaphore as will wait when no elements in the queue, so we now have blocking behaviour.
    sem->wait();

    // Aquiring the front lock
    std::lock_guard<std::mutex> lock(this->deqMutex);

    // Getting the payload from the node that is the actual front of the queue, not the payload from the dummy node.
    payload = this->front->next->payload;

    // Getting the node from the front, which is the current dummy node, so that it can be freed later
    auto toDelete = this->front;

    // Setting the front of the queue to be the next element, which basically makes the node that should be removed into the dummy node
    this->front = this->front->next;

    // Deletes the old dummy node
    delete toDelete;

    // Returns the payload from the node
    return payload;   
}

#endif

