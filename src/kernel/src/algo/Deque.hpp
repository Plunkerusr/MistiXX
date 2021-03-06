#pragma once

#include "../monitor.hpp"

namespace kernel {

template <typename T>
class DequeNode {
public:
    DequeNode() = default;

    DequeNode(const T& value)
    {
        m_value = new T(value);
    }
    DequeNode(T&& value)
    {
        m_value = new T(move(value));
    }

    ~DequeNode()
    {
        if (this->has_prev()) {
            this->prev().set_next(this->next());
        }
        if (this->has_next()) {
            this->next().set_prev(this->prev());
        }

        delete m_value;
    }

    T& operator*()
    {
        return *m_value;
    }

    bool has_next() const { return m_next; }
    bool has_prev() const { return m_prev; }

    inline DequeNode<T>& next() const { return *m_next; }
    inline DequeNode<T>& prev() const { return *m_prev; }

    void set_next(DequeNode<T>& next) { m_next = &next; }
    void set_prev(DequeNode<T>& prev) { m_prev = &prev; }

    void set_next(DequeNode<T>* next) { m_next = next; }
    void set_prev(DequeNode<T>* prev) { m_prev = prev; }

private:
    T* m_value { nullptr };
    DequeNode<T>* m_next { nullptr };
    DequeNode<T>* m_prev { nullptr };
};

template <typename Deque>
class DequeIterator {
    using ValueType = typename Deque::ValueType;
    friend Deque;

public:
    DequeIterator() = default;
    DequeIterator(DequeNode<ValueType>* ptr)
        : m_ptr(ptr)
    {
    }
    DequeIterator operator=(const DequeIterator& oth) {
        m_ptr = oth.m_ptr;
        return *this;
    }

    ValueType& operator*()
    {
        return **m_ptr;
    }

    ValueType* operator->()
    {
        return &(**m_ptr);
    }

    bool operator!=(const DequeIterator<Deque>& other) const
    {
        return m_ptr != other.m_ptr;
    }

    bool operator==(const DequeIterator<Deque>& other) const
    {
        return m_ptr == other.m_ptr;
    }

    DequeIterator<Deque>& operator++()
    {
        m_ptr = &m_ptr->next();
        return *this;
    }

    DequeIterator<Deque> operator++(int)
    {
        auto iter = *this;
        ++(*this);
        return iter;
    }

    DequeIterator<Deque>& operator--()
    {
        m_ptr = &m_ptr->prev();
        return *this;
    }

    DequeIterator<Deque> operator--(int)
    {
        auto iter = *this;
        --(*this);
        return iter;
    }

    DequeNode<ValueType>* ptr()
    {
        return m_ptr;
    }

private:
    DequeNode<ValueType>* m_ptr { nullptr };
};

template <typename T>
class Deque {
public:
    using ValueType = T;
    using Iterator = DequeIterator<Deque<ValueType>>;

    Deque()
    {
        m_head.set_next(m_tail);
        m_tail.set_prev(m_head);
    };

    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    void push_front(const ValueType& value)
    {
        auto* new_node = new DequeNode<ValueType>(value);

        new_node->set_prev(m_head);

        m_head.next().set_prev(new_node);
        new_node->set_next(m_head.next());

        m_head.set_next(new_node);

        m_size++;
    }

    void push_front(ValueType&& value)
    {
        auto* new_node = new DequeNode<ValueType>(move(value));

        new_node->set_prev(m_head);

        m_head.next().set_prev(new_node);
        new_node->set_next(m_head.next());

        m_head.set_next(new_node);

        m_size++;
    }

    void push_back(ValueType&& value)
    {
        auto* new_node = new DequeNode<ValueType>(move(value));

        new_node->set_next(m_tail);

        m_tail.prev().set_next(new_node);
        new_node->set_prev(m_tail.prev());

        m_tail.set_prev(new_node);

        m_size++;
    }


    void push_back(const ValueType& value)
    {
        auto* new_node = new DequeNode<ValueType>(value);

        new_node->set_next(m_tail);

        m_tail.prev().set_next(new_node);
        new_node->set_prev(m_tail.prev());

        m_tail.set_prev(new_node);

        m_size++;
    }

    Iterator find(const ValueType& value)
    {
        for (auto it = this->begin(); it != this->end(); it++) {
            if (*it == value) {
                return it;
            }
        }

        return end();
    }

    // removes element by its iterator,
    // returns previous element
    Iterator remove(const Iterator& del_it)
    {
        auto cp = del_it;
        cp--;
        delete del_it.m_ptr;
        m_size--;
        return cp;
    }

    Iterator begin()
    {
        return Iterator(&m_head.next());
    }
    Iterator end()
    {
        return Iterator(&m_tail);
    }
    Iterator rbegin()
    {
        return Iterator(&m_tail.prev());
    }
    Iterator rend()
    {
        return Iterator(&m_head);
    }

private:
    DequeNode<ValueType> m_head {};
    DequeNode<ValueType> m_tail {};

    size_t m_size {};
};
}