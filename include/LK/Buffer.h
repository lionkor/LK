#pragma once

#include "Algorithms.h"
#include "Meta.h"
#include "Types.h"

namespace LK {

/*
 * Base type for any class that relies on dynamic memory.
 * Because of this, it's kept very simple, and with a minimal API.
 */
template<typename T>
class Buffer {
public:
    explicit Buffer(size_t initial_size = 0)
        : m_data(new T[initial_size] {})
        , m_size(initial_size) {
    }
    virtual ~Buffer() {
        delete[] m_data;
    }

    void clear() {
        resize_to(0);
    }

    size_t used_memory_in_bytes() const {
        return sizeof(T) * m_size;
    }

    T& first() {
        LK_ASSERT(!empty());
        return m_data[0];
    }
    const T& first() const {
        LK_ASSERT(!empty());
        return m_data[0];
    }

    T& last() {
        LK_ASSERT(!empty());
        return m_data[m_size - 1];
    }

    const T& last() const {
        LK_ASSERT(!empty());
        return m_data[m_size - 1];
    }

    void append(const T& obj) {
        grow_by(1);
        m_data[m_size - 1] = obj;
    }

    void append(T&& obj) {
        grow_by(1);
        m_data[m_size - 1] = obj;
    }

    void grow_by(size_t n) {
        resize_to(m_size + n);
    }

    void shrink_by(size_t n) {
        if (n > m_size) {
            resize_to(0);
        } else {
            resize_to(m_size - n);
        }
    }

    void resize_to(size_t new_size) {
        if (new_size == 0) {
            delete[] m_data;
            m_data = nullptr;
        } else {
            T* new_data = new T[new_size] {};
            LK::Memory::move(new_data, m_data, LK::min(m_size, new_size));
            delete[] m_data;
            m_data = new_data;
        }
        m_size = new_size;
    }

    void fill(T&& value) {
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = value;
        }
    }

    void fill(const T& value) {
        for (size_t i = 0; i < m_size; ++i) {
            m_data[i] = value;
        }
    }

    bool empty() const {
        return m_size == 0 || m_data == nullptr;
    }

    size_t size() const {
        return m_size;
    }

    T& operator[](size_t n) {
        LK_ASSERT(n < m_size);
        return m_data[n];
    }

    T* data() { return m_data; }
    const T* data() const { return m_data; }

    class ConstIterator final {
    public:
        ConstIterator(const Buffer& buf, size_t i)
            : m_buffer(buf)
            , m_i(i) {
        }

        const T& operator*() const {
            return m_buffer[m_i];
        }
        const T& operator++() {
            return m_buffer[m_i++];
        }
        const T& operator++(int) {
            return m_buffer[++m_i];
        }
        const T& operator+=(size_t n) {
            return m_buffer[m_i += n];
        }
        bool operator==(const ConstIterator& iter) const {
            return iter.m_i == m_i;
        }
        bool operator!=(const ConstIterator& iter) const {
            return !(*this == iter);
        }

    private:
        const Buffer& m_buffer;
        size_t m_i;
    };

    class Iterator final {
    public:
        Iterator(Buffer& buf, size_t i)
            : m_buffer(buf)
            , m_i(i) {
        }

        T& operator*() const {
            return m_buffer[m_i];
        }
        T& operator++() {
            return m_buffer[m_i++];
        }
        T& operator++(int) {
            return m_buffer[++m_i];
        }
        T& operator+=(size_t n) {
            return m_buffer[m_i += n];
        }
        bool operator==(const Iterator& iter) const {
            return iter.m_i == m_i;
        }
        bool operator!=(const Iterator& iter) const {
            return !(*this == iter);
        }

    private:
        Buffer& m_buffer;
        size_t m_i;
    };

    friend class Iterator;
    friend class ConstIterator;

    ConstIterator begin() const { return ConstIterator(*this, 0); }
    Iterator begin() { return Iterator(*this, 0); }
    ConstIterator end() const { return ConstIterator(*this, m_size); }
    Iterator end() { return Iterator(*this, m_size); }

    bool operator==(const Buffer& buf) {
        return m_data == buf.m_data && m_size == buf.m_size;
    }
    bool operator!=(const Buffer& buf) {
        return !(*this == buf);
    }

private:
    T* m_data;
    size_t m_size;
};

}