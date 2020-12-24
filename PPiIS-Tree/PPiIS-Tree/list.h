#pragma once
#include <iostream>
#include <memory>
using namespace std;

template<class T>
class list {
public:
    list()
    {
        this->_size = 0;
        _list = nullptr;
    }
    void push_back(const T& data);
    void del(const T& data);
    int get_size();
    void insert(const int& ind, const T& data);
    bool check_existence(const T& data);
    T& operator[](const int& ind);
private:
    unique_ptr<T[]> _list;
    int _size;
};

template<class T>
inline void list<T>::push_back(const T& data)
{
    if (check_existence(data) == false)
    {
        unique_ptr<T[]> ndata = unique_ptr<T[]>(new T[_size + 1]);
        for (int i = 0; i < _size; i++)
            ndata[i] = move(_list[i]);

        ndata[_size] = data;
        _list = move(ndata);
        ++_size;
    }
}

template<class T>
inline void list<T>::del(const T& data)
{
    unique_ptr<T[]> deldata = unique_ptr<T[]>(new T[_size - 1]);

    int i = 0;
    while (_list[i] != data)
    {
        deldata[i] = move(_list[i]);
        ++i;
    }
    while (i < _size - 1)
    {
        deldata[i] = move(_list[i + 1]);
        ++i;
    }
    _list = move(deldata);
    --_size;
}

template<class T>
inline int list<T>::get_size()
{
    return _size;
}

template<class T>
inline void list<T>::insert(const int& ind, const T& data)
{

    if (check_existence(data) == false)
    {
        unique_ptr<T[]> ndata = unique_ptr<T[]>(new T[_size + 1]);

        int i = 0;
        while (i < ind)
        {
            ndata[i] = move(_list[i]);
            i++;
        }
        ndata[ind] = data;
        while (i < get_size())
        {
            ndata[i + 1] = move(_list[i]);
            i++;
        }
        _list = move(ndata);
        _size++;
    }
}

template<class T>
inline bool list<T>::check_existence(const T& data)
{

    for (int i = 0; i < _size; i++)
    {
        if (_list[i] == data)
            return true;
    }

    return false;
}

template<class T>
inline T& list<T>::operator[](const int& ind)
{
    return _list[ind];
}
