#pragma once
#include <iostream>
#include "list.h"

template<class T>
struct node {
    T _data;
    node* _parent;

    list<unique_ptr<node>> _childs;
    

    node(const T& data) :
        _data(data),
        _parent(nullptr)
    {   };
};


template<class T>
class tree {
public:
    tree() :
        root(nullptr)
    {   };

    void add_node(const T& parent, const T& data);
    node<T>* find_node(const T& data);
private:
    unique_ptr<node<T>> root;
    node<T>* data_list(node<T>* current, const T& data);
};

template<class T>
inline void tree<T>::add_node(const T& pdata, const T& cdata)
{
    unique_ptr<node<T>> nchild(new node<T>(cdata));

    if (root == nullptr)
    {
        unique_ptr<node<T>> nroot(new node<T>(pdata));
        root = nroot;
        root->childs.push_back(nchild);
        root->childs[root->_childs.get_size() - 1]->_parent = root.get();
    }


    node<T>* parent = find(pdata);
    node<T>* child = find(cdata);
    if (parent && !child)
    {
        parent->_childs.push_back(nchild);
        parent->_childs[parent->_childs.get_size() - 1]->_parent = parent;
    }
}

template<class T>
inline node<T>* tree<T>::find_node(const T& data)
{
    return NULL;
}

template<class T>
inline node<T>* tree<T>::data_list(node<T>* current, const T& data)
{
    if (current->_childs.get_size() == 0)
        return nullptr;

    if (current->_data == data)
        return current;

    for (int i = 0; i < cur->leaves.get_size(); i++)
    {
        node<T>* node_found = find_util(cur->leaves[i].get(), data);
        if (node_found) return node_found;
    }
}
