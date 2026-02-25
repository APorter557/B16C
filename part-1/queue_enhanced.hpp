#ifndef __queue_enhanced__
#define __queue_enhanced__

#include <cassert>
#include <vector>

#include "queue.hpp"

template <typename T> class Dequeue : public Queue<T>
{
  public:
    // Inherit the constructors of Queue<T>
    using Queue<T>::Queue;

    // Access the element at the back of the queue
    T &back()
    {
        // WRITE YOUR CODE HERE
        assert(Queue<T>::_size >= 1);
        if(Queue<T>::_position == Queue<T>::_storage.size() - 1) {
            return Queue<T>::_storage[0];
        } else {
            return Queue<T>::_storage[Queue<T>::_position + 1];
        }
    }

    // Const-access the element at the back of the queue
    const T &back() const
    {
        // WRITE YOUR CODE HERE
        assert(Queue<T>::_size >= 1);
        if(Queue<T>::_position == Queue<T>::_storage.size() - 1) {
            return Queue<T>::_storage[0];
        } else {
            return Queue<T>::_storage[Queue<T>::_position + 1];
        }
    }

    // Add a new element to the front of the queue by copying
    void enqueue_front(const T &value)
    {
        // WRITE YOUR CODE HERE
        Queue<T>::_size++;

        if (Queue<T>::_position + Queue<T>::_size > Queue<T>::_storage.size()) {
            Queue<T>::_storage[Queue<T>::_size + Queue<T>::_position - Queue<T>::_storage.size()] = value;
        }else{
            Queue<T>::_storage[Queue<T>::_position + Queue<T>::_size] = value;
        }

        }
    

    // Remove the element at the back of the queue
    void dequeue_back()
    {
        // WRITE YOUR CODE HERE
        assert(Queue<T>::_size >= 1);
        Queue<T>::_size--;
        if (Queue<T>::_position == Queue<T>::_storage.size() - 1) {
            Queue<T>::_position = 0;
        } else {
            Queue<T>::_position++;
        }
    }

    // Remove all elements from the queue
    void clear() { 
        // WRITE YOUR CODE HERE
        Queue<T>::_position = 0;
        Queue<T>::_size = 0;
    }

  protected:
    // Return the index of the element at the back of the queue
    size_t _tail() const
    {
        // WRITE YOUR CODE HERE
        assert(Queue<T>::_size >= 1);
        if(Queue<T>::_position == Queue<T>::_storage.size() - 1) {
            return Queue<T>::_position - Queue<T>::_position;       // Evaluates to 0 but ensures correct data type
        } else {
            return Queue<T>::_position + 1;
        }
    }
};

#endif // __queue_enhanced__