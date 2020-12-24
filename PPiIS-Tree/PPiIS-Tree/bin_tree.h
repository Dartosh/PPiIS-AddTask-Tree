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
    void del_node(node<T>* ptr);
    node<T>* find_node(const T& data);
    node<T>* data_list(node<T>* current, const T& data);
private:
    unique_ptr<node<T>> root;
};

template<class T>
inline void tree<T>::add_node(const T& pdata, const T& cdata)
{
    unique_ptr<node<T>> nchild(new node<T>(cdata));

    if (root == nullptr)
    {
        unique_ptr<node<T>> nroot(new node<T>(pdata));
        root = move(nroot);
        root->_childs.push_back(move(nchild));
        root->_childs[root->_childs.get_size() - 1]->_parent = root.get();
    }


    node<T>* parent = find_node(pdata);
    node<T>* child = find_node(cdata);
    if (parent && !child)
    {
        parent->_childs.push_back(nchild);
        parent->_childs[parent->_childs.get_size() - 1]->_parent = parent;
    }
}

template<class T>
inline void tree<T>::del_node(node<T>* ptr)
{
    if (ptr->_childs.get_size() == 0)
    {
        for (int i = 0; i < ptr->_parent->_childs.get_size(); ++i)
        {
            if (ptr->_parent->_childs[i].get() == ptr)
                ptr->_parent->_childs.del(ptr->_parent->_childs[i]);
        }
    }
    else if (ptr->_childs.get_size() == 1)
    {
        for (int i = 0; i < ptr->_parent->_childs.get_size(); ++i)
        {
            if (ptr->_parent->_childs[i].get() == ptr)
            {
                ptr->_parent->_childs.insert(i, ptr->_childs[0]);
                ptr->_parent->_childs.del(ptr->_parent->_childs[i + 1]);
            }
        }
    }
    else
    {
        node<T>* current = ptr->_childs[ptr->_childs.get_size() - 1].get();
        while (current->_childs.get_size() != 0)
            current = current->_childs[0].get();

        ptr->_data = current-> _data;
        del_node(current);
    }
}

template<class T>
inline node<T>* tree<T>::find_node(const T& data)
{
    return data_list(root.get(), data);
}

template<class T>
inline node<T>* tree<T>::data_list(node<T>* current, const T& data)
{
    if (current->_childs.get_size() == 0)
        return nullptr;

    if (current->_data == data)
        return current;

    for (int i = 0; i < current->_childs.get_size(); ++i)
    {
        node<T>* founded_node = data_list(current->_childs[i].get(), data);
        if (founded_node) 
            return founded_node;
    }
}
