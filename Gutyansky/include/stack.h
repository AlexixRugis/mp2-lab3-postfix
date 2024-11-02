#pragma once
#include <stdexcept>
#include <iostream>

#define STR1(x)  #x
#define STR(x)  STR1(x)

const int MaxStackSize = 100000000;

template <typename T>
class TStack
{
private:
    T* m_Memory;
    size_t m_Capacity;
    size_t m_Size;

public:
    TStack(size_t sizeToReserve = 0) : m_Capacity(0), m_Size(0), m_Memory(nullptr)
    {
        reserve(sizeToReserve);
    }

    TStack(const TStack& other)
    {
        m_Capacity = other.m_Capacity;
        m_Size = other.m_Size;
        m_Memory = new T[m_Size];
        std::copy(other.m_Memory, other.m_Memory + m_Size, m_Memory);
    }

    TStack(TStack&& other) noexcept
    {
        m_Capacity = other.m_Capacity;
        m_Size = other.m_Size;
        m_Memory = other.m_Memory;

        other.m_Size = 0;
        other.m_Capacity = 0;
        other.m_Memory = nullptr;
    }

    ~TStack()
    {
        delete[] m_Memory;
    }

    TStack& operator=(const TStack& other)
    {
        if (other.m_Capacity > m_Capacity)
        {
            T* tmp = new T[other.m_Capacity];
            delete[] m_Memory;
            m_Memory = tmp;
            m_Capacity = other.m_Capacity;
        }

        m_Size = other.m_Size;
        std::copy(other.m_Memory, other.m_Memory + m_Size, m_Memory);

        return *this;
    }

    TStack& operator=(TStack&& other) noexcept
    {
        if (m_Memory == other.m_Memory)
        {
            return *this;
        }

        m_Capacity = other.m_Capacity;
        m_Size = other.m_Size;
        m_Memory = other.m_Memory;

        other.m_Size = 0;
        other.m_Capacity = 0;
        other.m_Memory = nullptr;


        return *this;
    }

    size_t size() const noexcept
    {
        return m_Size;
    }

    size_t capacity() const noexcept
    {
        return m_Capacity;
    }

    bool empty() const noexcept
    {
        return size() == 0;
    }

    const T& top() const
    {
        if (empty())
        {
            throw std::logic_error("Stack is empty");
        }

        return m_Memory[size() - 1];
    }

    void pop()
    {
        if (empty())
        {
            throw std::logic_error("Can't pop from empty stack");
        }

        --m_Size;
    }

    void push(const T& elem)
    {
        if (m_Size == m_Capacity)
        {
            expand();
        }

        m_Memory[m_Size++] = elem;
    }

    void push(T&& elem)
    {
        if (m_Size == m_Capacity)
        {
            expand();
        }

        m_Memory[m_Size++] = std::move(elem);
    }

    void reserve(size_t newCapacity)
    {
        if (newCapacity > MaxStackSize)
        {
            throw std::length_error("Maximum stack length is " STR(MaxStackSize));
        }

        if (newCapacity <= capacity())
        {
            return;
        }

        T* tmp = new T[newCapacity];

        if (m_Memory != nullptr)
        {
            std::copy(m_Memory, m_Memory + m_Size, tmp);
            delete[] m_Memory;
        }

        m_Capacity = newCapacity;
        m_Memory = tmp;
    }

    friend void swap(TStack& lhs, TStack& rhs) noexcept
    {
        std::swap(m_Size, other.m_Size);
        std::swap(m_Capacity, other.m_Capacity);
        std::swap(m_Memory, other.m_Memory);
    }

    friend std::ostream& operator<<(std::ostream& os, const TStack& s)
    {
        for (size_t i = 0; i < s.size(); ++i)
        {
            os << s.m_Memory[i] << ' ';
        }

        return os;
    }

private:
    void expand()
    {
        const size_t reallocationFactor = 2;

        size_t newCapacity = std::max((size_t)1, m_Capacity * reallocationFactor);
        reserve(newCapacity);
    }
};
