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
    explicit Buffer(size_t initial_size = 0);
    virtual ~Buffer() {
        delete[] m_data;
    }
    // The amount of bytes the entire buffer uses.
    size_t used_memory_in_bytes() const;
    // The first element in the buffer.
    T& first();
    const T& first() const;
    // The last element in the buffer
    T& last();
    const T& last() const;
    // Grows the buffer to fit the to-be-appended memory, then
    // copies or moves the value(s) to the buffer.
    void append(const T& obj);
    void append(T&& obj);
    void append(const Buffer& buf);
    void append(Buffer&& buf);
    // Grows the buffer by n elements.
    void grow_by(size_t n);
    // Shrinks the buffer by n elements.
    void shrink_by(size_t n);
    // Resizes the buffer to n elements.
    void resize_to(size_t new_size);
    // Copies a slice from the buffer into a new buffer.
    Buffer slice(size_t from, size_t to);
    // Empties the buffer, same as resize_to(0).
    void clear();
    // Sets all elements in the buffer to the given value.
    void fill(T&& value);
    void fill(const T& value);
    // Whether the buffer is empty, i.e. has no elements. A lot of
    // functions do not work on empty buffers.
    bool empty() const { return m_size == 0 || m_data == nullptr; }
    // How many elements are in this buffer.
    size_t size() const { return m_size; }
    // Raw pointer to the internal data.
    T* data() { return m_data; }
    const T* data() const { return m_data; }

    T& operator[](size_t n);

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

    // Creates and returns an iterator pointing to the start of the buffer's data.
    ConstIterator begin() const { return ConstIterator(*this, 0); }
    Iterator begin() { return Iterator(*this, 0); }
    // Creates and returns an iterator pointing to the element past the end of the buffer's data.
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

template<typename T>
Buffer<T>::Buffer(size_t initial_size)
    : m_data(new T[initial_size] {})
    , m_size(initial_size) {
}

template<typename T>
void Buffer<T>::clear() {
    resize_to(0);
}

template<typename T>
size_t Buffer<T>::used_memory_in_bytes() const {
    return sizeof(T) * m_size;
}

template<typename T>
T& Buffer<T>::first() {
    LK_ASSERT(!empty());
    return m_data[0];
}

template<typename T>
const T& Buffer<T>::first() const {
    LK_ASSERT(!empty());
    return m_data[0];
}

template<typename T>
T& Buffer<T>::last() {
    LK_ASSERT(!empty());
    return m_data[m_size - 1];
}

template<typename T>
const T& Buffer<T>::last() const {
    LK_ASSERT(!empty());
    return m_data[m_size - 1];
}

template<typename T>
void Buffer<T>::append(const T& obj) {
    grow_by(1);
    m_data[m_size - 1] = obj;
}

template<typename T>
void Buffer<T>::append(T&& obj) {
    grow_by(1);
    m_data[m_size - 1] = obj;
}

template<typename T>
void Buffer<T>::append(const Buffer& buf) {
    auto old_size = m_size;
    grow_by(buf.size());
    LK::Memory::copy(m_data + old_size, buf.m_data, buf.size());
}

template<typename T>
void Buffer<T>::append(Buffer&& buf) {
    auto old_size = m_size;
    grow_by(buf.size());
    LK::Memory::move(m_data + old_size, buf.m_data, buf.size());
}

template<typename T>
void Buffer<T>::grow_by(size_t n) {
    resize_to(m_size + n);
}

template<typename T>
void Buffer<T>::shrink_by(size_t n) {
    if (n > m_size) {
        resize_to(0);
    } else {
        resize_to(m_size - n);
    }
}

template<typename T>
void Buffer<T>::resize_to(size_t new_size) {
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

template<typename T>
Buffer<T> Buffer<T>::slice(size_t from, size_t to) {
    LK_ASSERT(to >= from);
    LK_ASSERT(from <= m_size);
    LK_ASSERT(to <= m_size);
    Buffer buf(to - from);
    LK::Memory::copy(buf.m_data, m_data + from, to - from);
    return buf;
}

template<typename T>
void Buffer<T>::fill(T&& value) {
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = value;
    }
}

template<typename T>
void Buffer<T>::fill(const T& value) {
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = value;
    }
}

template<typename T>
T& Buffer<T>::operator[](size_t n) {
    LK_ASSERT(n < m_size);
    return m_data[n];
}

}