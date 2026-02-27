#ifndef __binary_tree_enhanced__
#define __binary_tree_enhanced__

#include <cassert>
#include <vector>
#include <memory>

// A class representing a binary tree
template <typename V> struct BinaryTreeEnhanced {
    V _value;
    std::unique_ptr<BinaryTreeEnhanced<V>> _left;
    std::unique_ptr<BinaryTreeEnhanced<V>> _right;

    // WRITE YOUR CODE HERE
    BinaryTreeEnhanced<V> *_parent;  // Can't be a unique_ptr because of ownership cycles
    // Constructor

    friend V &value(BinaryTreeEnhanced *t) { return t->_value; }
    friend const V &value(const BinaryTreeEnhanced *t)
    {
        return t->_value;
    }
    friend BinaryTreeEnhanced *left(const BinaryTreeEnhanced *t)
    {
        return t->_left.get();
    }
    friend BinaryTreeEnhanced *right(const BinaryTreeEnhanced *t)
    {
        return t->_right.get();
    }
    friend BinaryTreeEnhanced *parent(const BinaryTreeEnhanced *t)
    {
        // WRITE YOUR CODE HERE
        return t->_parent;
    }
};

// A helper function to build an enhanced binary tree
template <typename V>
std::unique_ptr<BinaryTreeEnhanced<V>>
make_binary_tree_enhanced(const V &value,
                          std::unique_ptr<BinaryTreeEnhanced<V>> l,
                          std::unique_ptr<BinaryTreeEnhanced<V>> r)
{
    // WRITE YOUR CODE HERE

    auto node_ptr = std::make_unique<BinaryTreeEnhanced<V>>();
    node_ptr->_value = value;
    node_ptr->_left = std::move(l);
    node_ptr->_right = std::move(r);

    if (node_ptr->_left) node_ptr->_left->_parent = node_ptr.get();
    if (node_ptr->_right) node_ptr->_right->_parent = node_ptr.get();

    return node_ptr;
}

#endif // __binary_tree_enhanced__