#include "doubly-linked-list.h"
#include <iostream>
#include <string>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    next = nullptr;
    prev = nullptr;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
        Node* cur = head_;
        Node* prev;

        for (int i = 0; i <= size_; i++)
        {
            if (cur != nullptr)
            {
                prev = cur;
                cur = cur->next;
                delete prev;
            }
        }

        head_ = nullptr;
        tail_ = nullptr;
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity()
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if (size_ == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DoublyLinkedList::full() const
{
    if (size_ == capacity()) // if the size is equal to capacity no more elements can be added
    {
        return true;
    }
    else
    {
        return false;
    }
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    Node* cur = head_;
    // if index of element is not in scope of list then invalid
    if (index >= size_ || index < 0)
    {
        Node* tmp = tail_;
        return tmp->value;// return last element of the list
    }

    // if list is empty
    if (head_ == nullptr)
    {
        return (DataType)-999;
    }

    // general case
    else
    {
        for (int i = 0; i < size_ ; i++)
        {
            if (i == index)
            {
                return (cur->value); // return value at current index
            }
            cur = cur->next;
        }
        return false;
    }

}
unsigned int DoublyLinkedList::search(DataType value) const
{
    Node* cur = head_;
    int position = 0;

    // iterate through list
    while (cur != nullptr)
    {
        //when value of current node equal value given
        if (cur->value == value)
        {
            return position;
        }
        position++;
        cur = cur->next;
    }
    return size_; // if value not in list, return size of list
}

void DoublyLinkedList::print() const
{
    Node* cur = head_;
    while (cur != nullptr)
    {
        cout << cur->value << endl;
        cur = cur->next;
    }

}
/*DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{

}*/

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    Node* cur = head_;
    Node* node = new Node(value);

    // can't add to list if there is no space (cap) or index isn't in list
    if (capacity() <= size_ || index > size_ || index < 0)
    {
        return false;
    }

    // if list is empty
    if (head_ == nullptr)
    {
        // head is new node
        head_ = node;
        size_++;
        return true;
    }

    // if inserting at front
    if (index == 0)
    {
        node->next = head_;
        head_->prev = node;
        head_ = node;
        size_++;
        return true;
    }
    if (size_ == index)
    {
        insert_back(value);
        return true;
    }
    else
    {
        // iterate through list until reach one node after index
        for (int i = 0; i <= index - 1; i++)
        {
            if ( i == index - 1)
            {
                node->next = cur->next;
                cur->next = node;
                node->prev = cur;
                node->next->prev = node;
                size_++;
                return true;
            }
            cur = cur->next;
        }
    }
    return false;
}

bool DoublyLinkedList::insert_front(DataType value)
{
    Node *node = new Node(value);

    // can't add to list if there is no space (cap)
    // or if size is less than one because would still have zero spaces
    if (capacity() <= size_ || 0 > size_)
    {
        return false;
    }

    // add element to empty list
    if (head_ == nullptr)
    {
        head_ = node;
        tail_ = node;
        size_++;
        return true;
    }

    // insert element at front of list
    node->next = head_;
    head_->prev = node;
    head_ = node;
    size_++;
    return true;
}

bool DoublyLinkedList::insert_back(DataType value)
{
    // can't fit in list if not adequate space
    if (size_ >= capacity() || 0 > size_)
    {
        return false;
    }
    else
    {
        Node* node = new Node(value);

        // insert node to empty list
        if (head_ == nullptr)
        {
            head_ = node;
            tail_ = node;
            size_++;
            return true;
        }
        else
        {
            // add new node to the end
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
            size_++;
            return true;
        }
    }
}

bool DoublyLinkedList::remove(unsigned int index)
{
    Node* cur = head_;
    if (size_ <= 0 || index >= size_)
        return false;

    else
    {
        // if head is index
        if (index == 0)
        {
            // if size is 1 element long
            if (size_ == 1)
            {
                head_ = nullptr;
                tail_ = nullptr;
                cur = nullptr;
                delete cur;
                size_--;
                return true;
            }
            // if list is more than 1 element long
            else
            {
                head_ = cur->next;
                cur = nullptr;
                delete cur;
                size_--;
                return true;
            }
        }
        else
        {
            // iterate though list
            int position = 0;
            while (cur != nullptr)
            {
                // find when position equals index
                if (position == index)
                {
                    // if index is tail
                    if (cur->next == nullptr)
                    {

                        tail_ = cur->prev;
                        cur = nullptr;
                        delete cur;
                        size_--;
                    }

                    // general cases
                    else
                    {
                        Node *prev = cur->prev;
                        prev->next = cur->next; // previous node points to the next node
                        prev = cur->next;
                        prev->prev = cur->prev;
                        cur = nullptr;
                        delete cur;
                        size_--;
                    }
                    return true;
                }
                position++;
            }
            return false;
        }
    }
}

bool DoublyLinkedList::remove_front()
{
   // list must have at least one element to remove
    if (size_ > 0)
    {
        Node* cur = head_;

        // list is one element long
        if (size_ == 1)
        {
            tail_ = nullptr;
            head_ = nullptr;
            cur = nullptr;
            delete cur;
            size_--;
            return true;
        }

        // if list is more than one element long
        while (cur == head_)
        {
            head_ = cur-> next;
            cur = nullptr;
            delete cur;
            size_--;
            return true;
        }
    }
    return false;
}

bool DoublyLinkedList::remove_back()
{
    // can't remove element if there is no element to remove
    if ( size_ == 0)
    {
        return false;
    }
    Node* cur = head_;

    // list is one element long
    if (size_ == 1)
    {
        head_ = nullptr;
        tail_ = nullptr;
        cur = nullptr;
        delete cur;
        size_--;
        return true;
    }

   // general case
    while (cur->next != nullptr)
    {
        if (cur->next == nullptr)
        {
            tail_ = cur->prev;
            cur = nullptr;
            delete cur;
            size_--;
            return true;
        }
        cur = cur->next;
    }
    return true;
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    Node* cur = head_;

    if (index < size_ && size_ > 0 && size_ < capacity())
    {
        int position = 0;
        while (cur != nullptr)
        {
            if (position == index)
            {
                cur->value = value;
                return true;
            }
            cur = cur->next;
            position++;
        }

    }
    return false;
}
