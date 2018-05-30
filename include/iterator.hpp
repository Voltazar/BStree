#include <iterator>
#include "Node.hpp"

namespace BStree {
template<typename T>
class BSTIterator : public std::iterator<std::bidirectional_iterator_tag, Node<T>> {
private:
    Node<T>* pointer;
    Node<T>* next(Node<T>*);
    Node<T>* prev(Node<T>*);
    auto min_el(Node<T>* )const -> Node<T>*;
    auto max_el(Node<T>* )const -> Node<T>*;
public:
    BSTIterator() : pointer{nullptr} {};
    BSTIterator(Node<T>* ptr) : pointer{ptr} {};
    BSTIterator(const BSTIterator& other) : pointer{other.pointer} {};
    auto operator=(const BSTIterator<T>& other)->BSTIterator<T>& ;
    auto operator++()->BSTIterator<T>& ;
    auto operator++(int)->BSTIterator<T> ;
    auto operator--()->BSTIterator<T>& ;
    auto operator--(int)->BSTIterator<T> ;
    auto operator*() const ->T& ;
    template<typename T1>
    auto friend operator==(BSTIterator<T1>& it, const BSTIterator<T1>& other)-> bool{
        if(it.pointer == other.pointer)
            return true;
        return false;
    }

    template<typename T2>
    auto friend operator!=(BSTIterator<T2>& it, const BSTIterator<T2>& other)-> bool {
        if(it.pointer != other.pointer)
            return true;
        return false;
    }

    template<typename T3>
    auto friend swap(BSTIterator<T3>& lhs, BSTIterator<T3>& rhs) -> void{
        std::swap(lhs.pointer, rhs.pointer);
    }

};

template<typename T>
auto BSTIterator<T>::min_el(Node<T>* node )const -> Node<T>* {
    if(node->left == nullptr)
        return node;
    while(node->left != nullptr)
        node = node ->left;
    return node;
}

template<typename T>
auto BSTIterator<T>::max_el(Node<T>* node )const -> Node<T>* {
    if(node->right == nullptr)
        return node;
    while(node->right != nullptr)
        node = node ->right;
    return node;
}

template<typename T>
auto BSTIterator<T>::next(Node<T>* node)->Node<T>* {
    if(node->right != nullptr)
        return min_el(node->right);
    Node<T>* parent_ = node->parent;
    while(parent_ != nullptr && node == parent_ ->right) {
        node = parent_;
        parent_= parent_->parent;
    }
    return parent_;
}

template<typename T>
auto BSTIterator<T>::prev(Node<T>* node)->Node<T>* {
    if(node->left != nullptr)
        return max_el(node->left);
    Node<T>* parent_ = node->parent;
    while(parent_ != nullptr && node == parent_ ->left) {
        node = parent_;
        parent_= parent_->parent;
    }
    return parent_;
}

template<typename T>
auto BSTIterator<T>::operator=(const BSTIterator<T>& other) ->BSTIterator<T>& {
    pointer = other.pointer;
    return *this;
}

template<typename T>
auto BSTIterator<T>::operator++()->BSTIterator<T>&  {
    pointer = next(pointer);
    return *this;
}

template<typename T>
auto BSTIterator<T>::operator++(int) ->BSTIterator<T> {
    BSTIterator<T> before (pointer);
    ++(*this);
    return before;

}

template<typename T>
auto BSTIterator<T>::operator--()->BSTIterator<T>&  {
    pointer = prev(pointer);
    return *this;
}

template<typename T>
auto BSTIterator<T>::operator--(int) ->BSTIterator<T> {
    BSTIterator<T> before (pointer);
    --(*this);
    return before;
}


template<typename T>
auto BSTIterator<T>::operator*() const -> T&  {
    return pointer->data;
}
}
