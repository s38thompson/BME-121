#include "dynamic-stack.h"
#include <iostream>
#include <string>
using namespace std;

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
    init_capacity_ = 16;
    capacity_ =  init_capacity_;
    items_ = new StackItem [capacity_];
    size_ = 0;
}

DynamicStack::DynamicStack(unsigned int capacity)
{
    // convert unsigned int into int
    int new_capacity = (int)capacity;
    init_capacity_ = new_capacity;
    capacity_ = init_capacity_;
    items_ = new StackItem [capacity_];
    size_ = 0;
}

DynamicStack::~DynamicStack()
{
    delete[] items_;
    items_ = nullptr;
}

bool DynamicStack::empty() const
{
    if (size_ == 0)
        return true;

    else
        return false;
}

int DynamicStack::size() const
{
    return size_;
}

void DynamicStack::push(StackItem value)
{
    // if capacity is greater than size
    if (size_ < capacity_)
    {
        // insert value at index size
        items_[size_] = value;
        // increase size
        size_++;
    }
    else
    {
        // double capacity
        capacity_ = (capacity_ * 2);
        // insert value at end
        items_[size_] = value;
        // increase size
        size_++;
    }
}

DynamicStack::StackItem DynamicStack::pop()
{
    // if empty, return empty stack constant
    if (empty())
        return EMPTY_STACK;

    else
    {
        // store item being popped into top variable
        int top = items_[size_ - 1];

        // delete last element of array
        size_ --;

        // if size is less than a quarter of capacity
        // and if initial capacity is less than or equal to half of capacity
        if ((capacity_ / 4) >= size_ && (capacity_ / 2) >= init_capacity_)
        {
            // half the capacity of the array
            capacity_ = (capacity_ / 2);

            // create temporary array to store first half
            int* items_temp = new int[capacity_];
            for (int i = 0; i < size_; i++)
            {
                // fill temporary array with first half of elements from items_
                items_temp[i] = items_[i];
            }

            // delete old items array
            delete[] items_;

            // store halved array into items
            items_ = items_temp;

        }
        // return old top
        return top;
    }
}

DynamicStack::StackItem DynamicStack::peek() const
{
    if (size_ == 0 || capacity_ < size_)
        return EMPTY_STACK;

    else
        return items_[size_ - 1];
}

void DynamicStack::print() const
{
    for (int i = 0; i < size_ ; i++)
    {
        cout << items_[i] << endl;
    }
}
