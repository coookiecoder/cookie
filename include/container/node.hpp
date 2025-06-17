#pragma once

#include <stdexcept>

#ifdef PROTECTION_ENABLED
#undef PROTECTION_ENABLED
#define PROTECTION_ENABLED true
#endif


#ifndef PROTECTION_ENABLED
#define PROTECTION_ENABLED false
#endif

namespace cookie {
    template <class Type>
    class Node {
        protected:
            Type* _data = nullptr;
            Node* _next = nullptr;
            Node* _prev = nullptr;

        public:
            explicit Node();
            explicit Node(const Type* data);
            explicit Node(const Type data);
            explicit Node(const Type& data);
            explicit Node(const Type&& data);

            void setNext(Node<Type>* next);
            void setPrev(Node<Type>* prev);

            Node* getNext();
            Node* getPrev();

            Node* clearNext();
            Node* clearPrev();

            Type& getData();

            ~Node();
    };
}

namespace cookie {

}

namespace cookie {
    template <class Type>
    Node<Type>::Node()
    {
        this->_data = new Type();
    }

    template <class Type>
    Node<Type>::Node(const Type* data)
    {
        this->_data = new Type(*data);
    }

    template <class Type>
    Node<Type>::Node(const Type data)
    {
        this->_data = new Type(data);
    }

    template <class Type>
    Node<Type>::Node(const Type& data)
    {
        this->_data = new Type(data);
    }

    template <class Type>
    Node<Type>::Node(const Type&& data)
    {
        this->_data = new Type(data);
    }

    template <class Type>
    void Node<Type>::setNext(Node<Type>* next)
    {
        if (PROTECTION_ENABLED && this->_next)
            throw std::runtime_error("Next node already set clear it first : ");
        this->_next = next;
    }

    template <class Type>
    void Node<Type>::setPrev(Node<Type>* prev)
    {
        if (PROTECTION_ENABLED && this->_prev)
            throw std::runtime_error("Previous node already set clear it first : ");
        this->_prev = prev;
    }

    template <class Type>
    Node<Type>* Node<Type>::getNext()
    {
        return this->_next;
    }

    template <class Type>
    Node<Type>* Node<Type>::getPrev()
    {
        return this->_prev;
    }

    template <class Type>
    Node<Type>* Node<Type>::clearNext()
    {
        Node* result = this->_next;

        if (this->_next)
            this->_next = this->_next->_next;
        else
            this->_next = nullptr;

        return result;
    }

    template <class Type>
    Node<Type>* Node<Type>::clearPrev()
    {
        Node* result = this->_prev;

        if (this->_prev)
            this->_prev = this->_prev->_prev;
        else
            this->_prev = nullptr;

        return result;
    }

    template <class Type>
    Type& Node<Type>::getData()
    {
        return *_data;
    }

    template <class Type>
    Node<Type>::~Node()
    {
        delete _data;
    }
}