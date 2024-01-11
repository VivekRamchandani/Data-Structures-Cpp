#pragma once
#include <iostream>

using std::ostream;

// Declarations
template <class T>
class DArray;
template <class T>
ostream& operator<<(ostream &stream, const DArray<T> &d_array);

const size_t DEFAULT_SIZE = 10;

template <class Array>
class ArrayIterator {
public:
    using Type = typename Array::Type;
public:
    ArrayIterator(Type* data)
        :array(data) {}
    
    // Increment and Decrement Operator
    ArrayIterator& operator++() {
        array++;
        return *this;
    }
    ArrayIterator operator++(int) {
        ArrayIterator temp = *this;
        ++(*this);
        return temp;
    }
    ArrayIterator& operator--() {
        array--;
        return *this;
    }
    ArrayIterator operator--(int) {
        ArrayIterator temp = *this;
        --(*this);
        return temp;
    }

    // Relation Operator
    bool operator==(const ArrayIterator &itr) const {
        return array == itr.array;
    }
    bool operator!=(const ArrayIterator &itr) const {
        return !(array == itr.array);
    }

    Type& operator*() {
        return *array;
    }

    Type& operator[](int idx) {
        return *(array + idx);
    }

    Type* operator->() {
        return array;
    }

private:
    Type* array;
};

template <class T>
class DArray
{
    T *array;
    size_t cap = DEFAULT_SIZE; // stores current capacity of darray
    size_t len = 0; // stores length
public:
    using Type = T;
    using Iterator = ArrayIterator<DArray<T>>;
public:
    DArray() {
        array = (T *)malloc(cap * sizeof(T));
    }
    DArray(size_t size);
    DArray(size_t size, T value);
    DArray(const DArray<T> &d_array);
    // DArray(DArray<T> &&d_array);
    ~DArray() { free(array); }
    
    void push(T value);
    void extend(const T arry[], int a_size);
    T pop() { return array[--len]; }
    int length() { return len; }
    int capacity() { return cap; }

    DArray<T> operator+(const DArray<T> &d_arry);
    DArray<T> operator+(const T value);
    DArray<T> operator-(const DArray<T> &d_arry);
    DArray<T> operator-(const T value);
    DArray<T> operator*(const DArray<T> &d_arry);
    DArray<T> operator*(const T value);
    DArray<T> operator/(const DArray<T> &d_arry);
    DArray<T> operator/(const T value);

    DArray<T>& operator=(const DArray<T> &d_arry);

    bool operator==(const DArray<T> &d_arry);
    bool operator<(const DArray<T> &d_arry);
    bool operator<=(const DArray<T> &d_arry);
    bool operator>(const DArray<T> &d_arry);
    bool operator>=(const DArray<T> &d_arry);

    T& operator[](int idx);

    friend ostream& operator<< <T>(ostream &stream, const DArray<T> &d_array);

    Iterator begin() {
        return Iterator(array);
    }
    Iterator end() {
        return Iterator(array + len);
    }
};

// Constructors
template <class T>
DArray<T>::DArray(size_t size)
{
    cap = size != 0 ? size : DEFAULT_SIZE;
    array = (T *)malloc(cap * sizeof(T));
    int i;
    for (i = 0; i < cap; i++)
        array[i] = T(0);
    len = cap;
}
template <class T>
DArray<T>::DArray(size_t size, T value)
{
    cap = size;
    array = (T *)malloc(cap * sizeof(T));
    int i;
    for (i = 0; i < cap; i++)
        array[i] = value;
    len = cap;
}
template <class T>
DArray<T>::DArray(const DArray<T> &d_array)
{
    cap = d_array.cap;
    len = d_array.len;
    array = (T *)malloc(cap * sizeof(T));
    int i;
    for (i = 0; i < len; i++)
        array[i] = d_array.array[i];
}

// Methods
template <class T>
void DArray<T>::push(T value)
{
    if (!(len - (cap - 1)))
    {
        cap += 4;
        array = (T *)realloc(array, cap * sizeof(T));
    }
    array[len++] = value;
}
template <class T>
void DArray<T>::extend(const T arry[], int a_size)
{
    int empty_space = len - cap;
    if (empty_space < a_size)
    {
        cap += (a_size - empty_space) + 4;
        array = (T *)realloc(array, cap * sizeof(T));
    }
    for (int i = 0; i < a_size; i++)
        array[len++] = arry[i];
}

// Arithmetic Operator Overload
template <class T>
DArray<T> DArray<T>::operator+(const DArray<T> &d_array)
{
    DArray<T> temp(len);
    int i;
    for (i = 0; i < d_array.len && i < len; i++)
        temp.array[i] = array[i] + d_array.array[i];
    return temp;
}
template <class T>
DArray<T> DArray<T>::operator+(const T value)
{
    DArray<T> temp(len, value);
    int i;
    for (i = 0; i < len; i++)
        temp.array[i] = array[i] + value;
    return temp;
}
template <class T>
DArray<T> DArray<T>::operator-(const DArray<T> &d_array)
{
    DArray<T> temp(len);
    int i;
    for (i = 0; i < d_array.len && i < len; i++)
        temp.array[i] = array[i] - d_array.array[i];
    return temp;
}
template <class T>
DArray<T> DArray<T>::operator-(const T value)
{
    DArray<T> temp(len, value);
    int i;
    for (i = 0; i < len; i++)
        temp.array[i] = array[i] - value;
    return temp;
}
template <class T>
DArray<T> DArray<T>::operator*(const DArray<T> &d_array)
{
    DArray<T> temp(len);
    int i;
    for (i = 0; i < d_array.len && i < len; i++)
        temp.array[i] = array[i] * d_array.array[i];
    return temp;
}
template <class T>
DArray<T> DArray<T>::operator*(const T value)
{
    DArray<T> temp(len, value);
    int i;
    for (i = 0; i < len; i++)
        temp.array[i] = array[i] * value;
    return temp;
}
template <class T>
DArray<T> DArray<T>::operator/(const DArray<T> &d_array)
{
    DArray<T> temp(len);
    int i;
    for (i = 0; i < d_array.len && i < len; i++)
        temp.array[i] = array[i] / d_array.array[i];
    return temp;
}
template <class T>
DArray<T> DArray<T>::operator/(const T value)
{
    DArray<T> temp(len, value);
    int i;
    for (i = 0; i < len; i++)
        temp.array[i] = array[i] / value;
    return temp;
}

// Assignment Operator Overload
template <class T>
DArray<T>& DArray<T>::operator=(const DArray<T> &d_array)
{
    cap = d_array.cap;
    len = d_array.len;
    array = (T *)malloc(cap * sizeof(T));
    int i;
    for (i = 0; i < len; i++)
        array[i] = d_array.array[i];
    return this;
}

// Relational Operator Overload
template <class T>
bool DArray<T>::operator==(const DArray<T> &d_arry)
{
    if (len == d_arry.len)
    {
        for (int i = 0; i < len; i++)
            if (array[i] != d_arry.array[i])
                return false;
        return true;
    }
    return false;
}
template <class T>
bool DArray<T>::operator<(const DArray<T> &d_arry)
{
    if (len < d_arry.len)
        return true;
    else if (len == d_arry.len)
    {
        for (int i = 0; i < len; i++)
            if (array[i] > d_arry.array[i])
                return false;
        if (array[len] == d_arry.array[len])
        {
            return false;
        }
        else
            return true;
    }
    return false;
}
template <class T>
bool DArray<T>::operator<=(const DArray<T> &d_array)
{
    if (len < d_array.len)
        return true;
    else if (len == d_array.len)
    {
        for (int i = 0; i < len; i++)
            if (array[i] > d_array.array[i])
                return false;
        return true;
    }
    else
        return false;
}
template <class T>
bool DArray<T>::operator>(const DArray<T> &d_arry)
{
    if (len > d_arry.len)
        return true;
    else if (len == d_arry.len)
    {
        for (int i = 0; i < len; i++)
            if (array[i] > d_arry.array[i])
                return false;
        if (array[len] == d_arry.array[len])
        {
            return false;
        }
        else
            return true;
    }
    else
        return false;
}
template <class T>
bool DArray<T>::operator>=(const DArray<T> &d_array)
{
    if (len > d_array.len)
        return true;
    else if (len == d_array.len)
    {
        for (int i = 0; i < len; i++)
            if (array[i] < d_array.array[i])
                return false;
        return true;
    }
    else
        return false;
}

// Slicing Operator Overload
template <class T>
T& DArray<T>::operator[] (int idx) {
    int calc_index = (idx < 0) ? len + idx : idx;
    if (calc_index < 0 || calc_index > len)
        throw std::out_of_range("Don't try to access out of range index, DUMBASS.");
    return array[calc_index];
}

// Insertor Operator Overload
template <class T>
ostream& operator<<(ostream &stream, const DArray<T> &d_array)
{
    stream << "[ ";
    int i;
    for (i = 0; i < d_array.len; i++)
        stream << d_array.array[i] << " ";
    stream << "]";

    return stream;
}