#pragma once

#define PROTECTION_ENABLED

#include <container/node.hpp>

namespace cookie {
    template <class Type>
    class List {
        protected:
            Node<Type>* _start = nullptr;

            unsigned long _size = 0;

        public:
            explicit List();
            explicit List(unsigned long size);

            void resize(unsigned long new_size);
            void shrink(unsigned long element_to_shrink);
            void expand(unsigned long element_to_expand);

            [[nodiscard]] unsigned long size() const;

            void push_back(const Type& data);
            void push_front(const Type& data);

            const Type& operator[](unsigned long index);

            ~List();
    };
}

namespace cookie {

}

namespace cookie {
    template <class Type>
    List<Type>::List() = default;

    template <class Type>
    List<Type>::List(const unsigned long size)
    {
        this->_start = new Node<Type>;

        Node<Type>* current = this->_start;

        for (int list_size = 1; list_size < size; ++list_size) {
            current->setNext(new Node<Type>);
            current = current->getNext();
        }

        this->_size = size;
    }

    template <class Type>
    void List<Type>::resize(unsigned long new_size)
    {
        if (new_size == this->_size)
            return;

        if (new_size < this->_size)
            return this->shrink(this->_size - new_size);

        if (new_size > this->_size)
            return this->expand(new_size - this->_size);

        throw std::runtime_error("Unreachable code");
    }

    template <class Type>
    void List<Type>::shrink(unsigned long element_to_shrink)
    {
        Node<Type>* current = this->_start;

        for (int list_size = 1; list_size < this->_size - element_to_shrink; ++list_size)
            current = current->getNext();

        while (current->getNext())
            delete current->clearNext();

        this->_size -= element_to_shrink;
    }

    template <class Type>
    void List<Type>::expand(unsigned long element_to_expand)
    {
        Node<Type>* current = this->_start;

        while (current->getNext())
            current = current->getNext();

        for (int list_size = 0; list_size < element_to_expand; ++list_size) {
            current->setNext(new Node<Type>);
            current = current->getNext();
        }

        this->_size += element_to_expand;
    }

    template <class Type>
    unsigned long List<Type>::size() const
    {
        return this->_size;
    }

    template <class Type>
    void List<Type>::push_back(const Type& data)
    {
        if (this->_start)
        {
            auto buffer = new Node<Type>(&data);
            Node<Type>* current = this->_start;

            while (current->getNext())
                current = current->getNext();

            current->setNext(buffer);
            ++this->_size;
        }
        else
        {
            this->_start = new Node<Type>(&data);
            ++this->_size;
        }
    }

    template <class Type>
    void List<Type>::push_front(const Type& data)
    {
        if (this->_start)
        {
            auto buffer = new Node<Type>(&data);

            buffer->setNext(this->_start);
            this->_start = buffer;
        }
        else
        {
            this->_start = new Node<Type>(&data);
            ++this->_size;
        }
    }

    template <class Type>
    const Type& List<Type>::operator[](unsigned long index)
    {
        Node<Type>* current = this->_start;

        for (int list_size = 0; list_size < index; ++list_size)
            current = current->getNext();

        return current->getData();
    }


    template <class Type>
    List<Type>::~List()
    {
        if (this->_start)
        {
            Node<Type>* current = this->_start;

            this->_start = this->_start->getNext();

            for (int list_size = 1; list_size < this->_size; ++list_size)
            {
                delete current;

                current = this->_start;
                this->_start = this->_start->getNext();
            }

            delete current;
        }
    }
}