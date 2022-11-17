#include "circular-queue.h"
#include <iostream>
#include <string>
using namespace std;

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
    capacity_ =  16;
    items_ = new QueueItem [capacity_];
    head_ = tail_ = -1;
    size_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity)
{
    // convert unsigned int into int
    int new_capacity = (int)capacity;
    capacity_ = new_capacity;
    items_ = new QueueItem [capacity_];
    head_ = tail_ = -1;
    size_ = 0;
}

CircularQueue::~CircularQueue()
{
    delete[] items_;
    items_ = nullptr;
}

bool CircularQueue::empty() const
{
    // if no elements in queue
    if (size_ == 0)
        return true;

    else
        return false;
}

bool CircularQueue::full() const
{
    // if queue cannot hold anymore elements
    if (size_ == capacity_)
        return true;

    else
        return false;
}

int CircularQueue::size() const
{
    return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
    // if queue is full
    if (full())
        return false;

    else
    {
        // inserting first element of list
        if (head_ == - 1)
        {
            head_ = 0;
            tail_ = 0;
        }

        items_[tail_] = value; // insert element
        tail_ = (tail_ + 1) % capacity_; // going around in circle
        size_++; // increase size
        return true;
    }
}

CircularQueue::QueueItem CircularQueue::dequeue()
{
    if (empty())
        return EMPTY_QUEUE;

    else
    {
        // store the front index into variable
        int front = items_[head_];
        head_ = (head_ + 1) % capacity_;

        if (head_ == tail_)
        {
            head_ = - 1;
            tail_ = - 1;
        }

        size_--;
        return front;
    }
}

CircularQueue::QueueItem CircularQueue::peek() const
{
    if (empty())
        return EMPTY_QUEUE;

    else
        return items_[head_];
}

void CircularQueue::print() const
{
    for (int i = 0; i < size_ ; i++)
    {
        cout << items_[i] << endl;
    }
}