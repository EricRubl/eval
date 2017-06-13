//
// Created by Eric on 11.06.2017.
//

#ifndef EVAL_DYNAMICSTACK_HPP
#define EVAL_DYNAMICSTACK_HPP

namespace Eval
{
    template <typename stack_elem_t>
    struct Node
    {
        stack_elem_t element;
        Node<stack_elem_t>* next;
    };

    template <typename stack_elem_t>
    class DynamicStack
    {
    private:
        Node<stack_elem_t>* first;
        unsigned long long* _size;
    public:
        DynamicStack() { first = nullptr; _size = new unsigned long long(0); }
        ~DynamicStack()
        {
            while(!this->empty())
                pop();
            delete _size;
        }

        bool empty() const noexcept
        {
            return first == nullptr;
        }

        void push(stack_elem_t element) noexcept
        {
            Node<stack_elem_t>* newNode = new Node<stack_elem_t>;
            newNode->element = element;
            if(this->empty())
                newNode->next = nullptr;
            else
                newNode->next = first;
            first = newNode;
            (*_size)++;
        }

        void pop() noexcept
        {
            if(this->empty())
                return;
            Node<stack_elem_t>* temp = first;
            first = temp->next;
            delete temp;
            (*_size)--;
        }

        stack_elem_t top() const
        {
            if(empty())
                throw "Stack is empty!";
            else
                return first->element;
        }
    };
}



#endif //EVAL_DYNAMICSTACK_HPP
