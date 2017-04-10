//
// Created by Andrei Gavrila on 29.03.2017.
//

#ifndef LMDB_VECTOR_H
#define LMDB_VECTOR_H

#include <exception>
#include <functional>
#include <iterator>

template<class T>
class Vector {
    
    T* elements = nullptr;
    unsigned _capacity = 0;
    unsigned _size = 0;
    static constexpr float resizingFactor = 2.0;
public:
    Vector();
    
    Vector(unsigned initialSize);
    
    Vector(Vector& v);
    
    Vector(Vector&& v);
    
    Vector& operator =(Vector&& other);
    
    Vector& operator =(Vector& other);
    
    ~Vector();
    
    unsigned size() const;
    
    /// @brief Resizes the vector to a new capacity
    /// @param newSize The new size
    void resize(unsigned newSize);
    
    /// @brief Pushse the element to the end of the array
    /// @param el The element to be added
    void push_back(const T& el);
    
    /// @brief Removes the idth element
    /// @param id
    void remove(int id);
    
    T& operator [](int i);
    
    /// @brief Returns the id of the first element that is equal to the given one
    /// @return
    int findFirstId(const T&) const;
//    bool findFirstCallback(const T&, void (*callback)(T));
    
    /// @brief Removes the element matching el from the vector
    /// @param el The element to be removed
    /// @return
    Vector<T>& operator -(const T& el);
    
    /// @brief Returns a pointer to a enw vector containing the filtered elements
    /// @param condition The filterer
    /// @return
    Vector<T>* filter(std::function<bool(T&)> condition);
    
    /// @brief Used for range for
    /// @return
    T* begin();
    
    /// @brief Used for range for
    /// @return
    T* end();
};

template<class T>
void Vector<T>::resize(unsigned newSize) {
    T* newElements = new T[newSize];
    
    if (newSize < this->_size) {
        this->_size = newSize;
    }
    this->_capacity = newSize;
    for (int i = 0; i < this->_size; i++) {
        newElements[i] = this->elements[i];
    }
    
    delete[] this->elements;
    this->elements = newElements;
}

//template<class T>
//bool Vector<T>::findFirstCallback(const T& obj, void (*callback)(T)) {
//    int i = this->findFirstId(obj);
//    if (i == -1) {
//        return false;
//    } else {
//        callback(this->elements[i]);
//        return true;
//    }
//}

template<class T>
Vector<T>::Vector(Vector& v) {
    this->resize(v.size());
    for (int i = 0; i < v.size(); i++) {
        this->elements[i] = v[i];
    }
}

template<class T>
Vector<T>::Vector(Vector&& v) {
    this->resize(v.size());
    for (int i = 0; i < v.size(); i++) {
        this->elements[i] = v[i];
    }
}

template<class T>
void Vector<T>::push_back(const T& el) {
    if (this->_size == this->_capacity) {
        this->resize(this->_capacity == 0? 1 : (unsigned)(this->_capacity * this->resizingFactor));
    }
    
    this->elements[this->_size++] = el;
}

template<class T>
Vector<T>::~Vector() {
    if (this->elements != nullptr) {
        delete[] this->elements;
    }
}

template<class T>
Vector<T>::Vector(unsigned initialSize) {
    this->_capacity = initialSize;
    this->elements = new T[initialSize];
}

template<class T>
unsigned Vector<T>::size() const {
    return this->_size;
}

template<class T>
T& Vector<T>::operator [](int i) {
    if (this->size() == 0) {
        throw std::logic_error("Void vector.");
    }
    i %= this->size();
    return this->elements[i < 0? this->size() + i : unsigned(i)];
}

template<class T>
void Vector<T>::remove(int id) {
//    delete this->elements[id];
    
    this->_size--;
    for (int i = id; i < this->size(); i++) {
        this->elements[i] = this->elements[i + 1];
    }
}

template<class T>
int Vector<T>::findFirstId(const T& obj) const {
    for (int i = 0; i < this->size(); i++) {
        if (this->elements[i] == obj) {
            return i;
        }
    }
    return -1;
}

template<class T>
T* Vector<T>::begin() {
    return this->elements;
}

template<class T>
T* Vector<T>::end() {
    return this->elements + this->_size;
}

template<class T>
Vector<T>& Vector<T>::operator =(Vector&& other) {
    delete[] this->elements;
    
    this->resize(other.size());
    for (int i = 0; i < other.size(); ++i) {
        this->elements[i] = other[i];
    }
    
    return *this;
}

template<class T>
Vector<T>::Vector() {
    this->elements = nullptr;
    this->_capacity = 0;
    this->_size = 0;
}

template<class T>
Vector<T>* Vector<T>::filter(std::function<bool(T&)> condition) {
    auto fil = new Vector<T>();
    
    for (auto& t: *this) {
        if (condition(t)) {
            fil->push_back(t);
        }
    }
    
    return fil;
}

template<class T>
Vector<T>& Vector<T>::operator =(Vector& other) {
    delete[] this->elements;
    
    this->resize(other.size());
    for (int i = 0; i < other.size(); ++i) {
        this->elements[i] = other[i];
    }
    
    return *this;
}

template<class T>
Vector<T>& Vector<T>::operator -(const T& el) {
    int tid = this->findFirstId(el);
    if (tid != -1) {
        this->remove(tid);
    }
    return *this;
}

#endif //LMDB_VECTOR_H
