#pragma once
#include <iostream>
using namespace std;

template<class T>
class list {
public:
    list() :
        _size(0),
        _list(nullptr)
    {    }
    void push_back(const T& data);
    void del(const T& data);
    int get_size();
    T& operator[](const int& ind);
private:
    unique_ptr<T[]> _list;
    int _size;
};

template<class T>
inline void list<T>::push_back(const T& data)
{
    unique_ptr<T[]> ndata = unique_ptr<T[]>(new T[size + 1]);
    for (int i = 0; i < size; ++i)
        ndata[i] = _list[i];

    ndata[_size] = data;
    _list = ndata;
    ++size;
}

template<class T>
inline void list<T>::del(const T& data)
{
    unique_ptr<T[]> deldata = unique_ptr<T[]>(new T[size - 1]);

    int i = 0;
    while (_list[i] != data)
    {
        deldata[i] = _list[i];
        ++i;
    }
    while (i < _size - 1)
    {
        deldata[i] = _list[i + 1];
        ++i;
    }
    _list = deldata;
    --_size;
}

template<class T>
inline int list<T>::get_size()
{
    return _size;
}

template<class T>
inline T& list<T>::operator[](const int& ind)
{
    return _list[ind];
}
