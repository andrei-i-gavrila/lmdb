//
// Created by Andrei Gavrila on 30.03.2017.
//

#ifndef LMDB_DATABASE_H
#define LMDB_DATABASE_H

#include <string>
#include "../domain/movie.h"
#include "../utils/vector.h"

template<class T>

class Database {
private:
    Vector<T>* elements = nullptr;

public:
    Database();
    
    Database(const Database& d);
    
    Database& operator =(Database& d);
    
    ~Database();
    
    /// @brief Adds m to the database
    /// @param m
    void add(T& m);
    
    /// @brief Removes The obj from the database
    /// @param obj
    /// @return
    bool remove(const T& obj);
    
    
    /// @brief Returns the id of the first matching element
    /// @param obj
    /// @return
    int find(const T& obj);
    
    /// @brief overloading array operator
    /// @param id
    /// @return
    T& operator [](int id);
    
    int size();
    
    T* begin();
    
    T* end();
    
    Vector<T>& getAll();

private:
    
    /// @brief Removes the idth element
    /// @param id
    void removeId(int id);
};

template<class T>
int Database<T>::find(const T& obj) {
    return this->elements->findFirstId(obj);
}

template<class T>
bool Database<T>::remove(const T& obj) {
    int id = this->find(obj);
    if (id == -1) {
        return false;
    }
    
    this->elements = &((*this->elements) - obj);
    return true;
}

template<class T>
T& Database<T>::operator [](int id) {
    return (*(this->elements))[id];
}

template<class T>
void Database<T>::add(T& m) {
    
    this->elements->push_back(m);
    
}

template<class T>
Database<T>::~Database() {
    if (this->elements != nullptr)
        delete this->elements;
}

template<class T>
void Database<T>::removeId(int id) {
    this->elements->remove(id);
}

template<class T>
Database<T>::Database() {
    this->elements = new Vector<T>();
}

template<class T>
int Database<T>::size() {
    return this->elements->size();
}

template<class T>
Database<T>::Database(const Database& d) {
    this->elements = new Vector<T>(*d.elements);
}

template<class T>
Database<T>& Database<T>::operator =(Database& d) {
    this->elements = new Vector<T>(*d.elements);
    return *this;
}

template<class T>
T* Database<T>::begin() {
    return this->elements->begin();
}

template<class T>
T* Database<T>::end() {
    return this->elements->end();
}

template<class T>
Vector<T>& Database<T>::getAll() {
    return *(this->elements);
}

#endif //LMDB_DATABASE_H
