//
// Created by Eric on 12.06.2017.
//

#ifndef EVAL_DYNAMICQUEUE_HPP
#define EVAL_DYNAMICQUEUE_HPP

namespace Eval
{
    template <typename queue_elem_t, unsigned long long capacity = 50>
    struct LinkedList
    {
        queue_elem_t* data;
        unsigned long long* next;

        LinkedList() { data = new queue_elem_t[capacity]; next = new unsigned long long[capacity]; for(unsigned long long i(0); i < capacity; ++i) next[i] = 0; }
        ~LinkedList() {delete[] data; delete[] next; }


        void add(queue_elem_t element)
        {
            for(unsigned long long i(0); i < capacity; ++i)
                if(next[i] == 0)
                    if(i == 0){
                        data[0] = element;
                        next[0] = 1;
                        break;
                    }
                    else
                    {
                        data[i] = element;
                        next[i] = i + 1;
                        break;
                    }
        }
    };

    template <typename queue_elem_t, unsigned long long capacity = 50>
    class DynamicQueue
    {
    private:
        LinkedList<queue_elem_t, capacity> list;
        unsigned long long* _size;
    public:
        DynamicQueue() { _size = new unsigned long long(0); }
        ~DynamicQueue() { delete _size; }

        bool empty() const noexcept
        {
            return (*_size) == 0;
        }

        void push(queue_elem_t element)
        {
            if((*_size) == capacity)
                throw "Queue is full!";
            list.add(element);
            (*_size)++;
        }

        void pop() noexcept
        {
            if(empty())
                return;
            for(unsigned long long i(0); i < (*_size) - 1; ++i)
                list.data[i] = list.data[i + 1];
            if((*_size) == 1)
                list.next[0] = 0;
            else
                list.next[(*_size) - 2] = 0;
            (*_size)--;
        }

        queue_elem_t front() const
        {
            if(empty())
                throw "Queue is empty!";
            return list.data[0];
        }
    };
}

#endif //EVAL_DYNAMICQUEUE_HPP
