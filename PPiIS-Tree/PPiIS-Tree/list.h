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
