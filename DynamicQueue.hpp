//
// Created by Eric on 12.06.2017.
//

#ifndef EVAL_DYNAMICQUEUE_HPP
#define EVAL_DYNAMICQUEUE_HPP

namespace Eval
{
    template <typename queue_elem_t>
    struct IndexNode
    {
        queue_elem_t element;
        unsigned long long next = 0;
    };

    template <typename queue_elem_t, constexpr unsigned long long capacity>
    class DynamicQueue
    {
    private:
        IndexNode<queue_elem_t>* nodes;
        unsigned long long* _size;
    public:
        DynamicQueue() { nodes = new IndexNode<queue_elem_t>[capacity]; _size = new unsigned long long(0); }
        ~DynamicQueue() { delete nodes; delete _size; }

        bool empty() const
        {
            return (*_size) == 0;
        }

        void push(queue_elem_t element)
        {
            if((*_size) == capacity)
                throw "Queue is full!";
            nodes[(*_size)].element = element;
            if((*_size) > 0)
                nodes[(*_size) - 1].next = (*_size);
            (*_size)++;
        }

        void pop()
        {
            if(empty())
                return;
            for(unsigned long long i(0); nodes[i].next not_eq 0; ++i)
                nodes[i].element = nodes[i + 1].element;
            if((*_size) > 0)
                nodes[(*_size) - 1].next = 0;
            else
                nodes[(*_size)].next = 0;
            (*_size)--;
        }

        unsigned long long size() const
        {
            return (*_size);
        }

        queue_elem_t front() const
        {
            if(empty())
                throw "Queue is empty!";
            return nodes[0].element;
        }

        queue_elem_t back() const
        {
            if(empty())
                throw "Queue is empty!";
            for(unsigned long long i(0); i < capacity; ++i)
                if(nodes[i].next == 0)
                    return nodes[i].element;
        }
    };
}

#endif //EVAL_DYNAMICQUEUE_HPP
