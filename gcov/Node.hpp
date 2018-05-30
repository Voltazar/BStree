#ifndef __NODE_HPP__
#define __NODE_HPP__

namespace BStree {

template <typename T>
struct Node {
    T data ;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    Node(T value) : data{value}, left{nullptr}, right{nullptr}, parent{nullptr} {};
};
}
#endif