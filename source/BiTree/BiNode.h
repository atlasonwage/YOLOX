#pragma once
#include <string>

template<typename KEY, typename VALUE>
class BiNode {
    BiNode();
    ~BiNode();

    KEY key;
    VALUE value;
    BiNode* left;
    BiNode* right;
    int height;

    friend class BiTree;
};



template<typename KEY, typename VALUE>
BiNode<KEY, VALUE>::BiNode() {
    value = "?";
    left = nullptr;
    right = nullptr;
    height = 0;
}

template<typename KEY, typename VALUE>
BiNode<KEY, VALUE>::~BiNode() {
    delete left;
    delete right;
    left = nullptr;
    right = nullptr;
}