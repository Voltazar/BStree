#ifndef __TREE_HPP__
#define __TREE_HPP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Node.hpp>
#include <iterator.hpp>


namespace BStree {

enum class traversal_order {pre, in, post};

template <typename T>
class Tree {
    Node<T>* root;
    auto print_root(const Node<T>* node) -> void;
    auto destructor(Node<T>* node) -> void;
public:

    Tree() {
        root = nullptr;
    }
    Tree(std::initializer_list<T> list);
    Tree(const Tree<T>& tree);
    auto remove(T value)->bool;
    auto search(T value) const -> bool;
    auto swap(Tree<T>& tree) -> void;
    auto add(T value) -> bool;
    auto empty() const -> bool;
    auto print() -> void;
    auto save(const std::string& path) -> bool;
    auto load(const std::string& path) -> bool;
    auto print_order(std::ostream& stream, traversal_order order) const -> std::ostream&;
    template <typename T1>
    auto friend operator<<(std::ostream& stream, const Tree<T1>& tree) -> std::ostream& {
        return tree.print_order(stream, BStree::traversal_order::pre);
    }
    auto operator=(const Tree<T>& tree) -> Tree<T>&;

    auto begin() -> BSTIterator<T> {
        Node<T>* node = root;
        while(node->left!=nullptr)
            node = node->left;
        BSTIterator<T> it (node);
        return it;
    }

    auto end() -> BSTIterator<T> {
        Node<T>* node = root;
        while(node->right!=nullptr)
            node = node->right;
        BSTIterator<T> it (node);
        return it;
    }

    auto rbegin() -> BSTIterator<T> {
        Node<T>* node = root;
        while(node->right!=nullptr)
            node = node->right;
        BSTIterator<T> it (node);
        return it;
    }

    auto rend() -> BSTIterator<T> {
        Node<T>* node = root;
        while(node->left!=nullptr)
            node = node->left;
        BSTIterator<T> it (node);
        return it;
    }

    ~Tree() {
        destructor(root);
    }


};
}

template <typename T>
auto BStree::Tree<T>::operator=(const Tree<T>& tree) -> Tree<T>&{
    Tree tmp {tree};
    tmp.swap(*this);
    return *this;
}

template <typename T>
BStree::Tree<T>::Tree(std::initializer_list<T> list) {
    root = nullptr;
    for (auto x: list ) {
        this->add(x);
    }
}

template <typename T>
BStree::Tree<T>::Tree(const Tree<T>& tree) : Tree{} {
    std::string str;
    std::stringstream out(str);
    out << tree;
    T value;
    while(out) {
        out >> value;
        this->add(value);
    }
}

template <typename T>
auto BStree::Tree<T>::search(T value) const -> bool {
    if(root == nullptr)
        return false;
    Node<T>* node = root;
    while (node->data != value) {
        if(node->data > value)
            node = node -> left;
        else
            node = node -> right;
        if(node == nullptr)
            return false;
    }
    return true;
}

template <typename T>
auto BStree::Tree<T>::add(T value) -> bool {
    if(search(value))
        return false;
    if (root == nullptr) {
        root = new Node<T> {value};
        root -> parent = nullptr;
        return true;
    }
    Node<T>* node = root;
    while(node != nullptr) {
        if(node->data > value ) {
            if(node -> left == nullptr) {
                node -> left = new Node<T> {value};
                node -> left -> parent = node;
                break;
            }
            node = node -> left;
        } else {

            if(node -> right == nullptr) {
                node -> right = new Node<T> {value};
                node -> right -> parent = node;
                break;
            }
            node = node -> right;

        }
    }
    return true;
}

template <typename T>
auto BStree::Tree<T>::print() -> void {
    if(root == nullptr) {
        std::cout <<"\033[1;31mДерево пусто!\033[0;37m\U0001F631\033[0;34m" <<std::endl;
        return;
    }
    print_root(root);
}

template <typename T>
auto BStree::Tree<T>::print_root(const Node<T>* node ) -> void {
    if(node != nullptr) {
        static size_t  indent = 0;
        if(node == root) {
            print_root(node->right);
            std::cout<<std::endl;
            std::cout<<" \033[1;32m"<<node->data;
            std::cout << std::endl << std::endl;
            print_root(node->left);
            return;
        }
        indent++;
        print_root(node->right);
        for(size_t i = 0; i < indent; i++)
            std::cout<<"     ";
        std::cout<<"\033[0;33m\U00002053 \033[1;32m"<<node->data<<std::endl;
        print_root(node->left);
        indent--;
        return;
    }
}

template <typename T>
auto print_pre(std::ostream& out, const BStree::Node<T>* node) -> std::ostream& {
    if(node != nullptr) {
        out << node->data<<"  ";
        print_pre(out, node->left);
        print_pre(out, node->right);
    }
    return out;
}

template <typename T>
auto print_in(std::ostream& out, const BStree::Node<T>* node)-> std::ostream& {
    if(node != nullptr) {
        print_in(out,node->left);
        out << node->data<<"  ";
        print_in(out,node->right);
    }
    return out;
}

template <typename T>
auto print_post(std::ostream& out, const BStree::Node<T>* node)  -> std::ostream& {
    if(node != nullptr) {
        print_post(out,node->left);
        print_post(out,node->right);
        out << node->data<<"  ";
    }
    return out;
}


template <typename T>
auto BStree::Tree<T>::print_order(std::ostream& out, BStree::traversal_order order) const  -> std::ostream& {
    if(order == traversal_order::pre) {
        print_pre(out,root);
    } else if (order == traversal_order::in) {
        print_in(out,root);
    } else {
        print_post(out,root);
    }
    return out;
}

template <typename T>
auto BStree::Tree<T>::swap(Tree<T>& tree) -> void {
    std::swap(root, tree.root);
}

template <typename T>
auto BStree::Tree<T>::destructor(Node<T>* node) -> void {
    if(node != nullptr) {
        destructor(node->left);
        destructor(node->right);
        delete node;
    }
    node = nullptr;
}

template <typename T>
auto BStree::Tree<T>::remove(T value)-> bool{
    if(!search(value))
        return false;
    Node<T>* pointer = root;
    Node<T>* parent_  = nullptr;

    while( pointer->data != value) {
        parent_ = pointer;
        if(value < pointer->data)
            pointer = pointer->left;
        else
            pointer = pointer->right;
    }

    Node<T>* removed = nullptr;

    if (pointer->left == nullptr || pointer->right == nullptr) {
        Node<T>* child = nullptr;
        removed = pointer;

        if(pointer->left != nullptr)
            child = pointer->left;
        else if(pointer->right != nullptr)
            child = pointer->right;

        if(parent_ == nullptr)
            root = child;
        else {
            if(parent_->left == pointer)
                parent_->left = child;
            else
                parent_->right = child;
            if(child != nullptr)
                child -> parent = parent_;

        }
    } else {
        Node<T>* mostLeft = pointer->right;
        Node<T>* mostLeftParent = pointer;

        while (mostLeft->left != nullptr) {
            mostLeftParent = mostLeft;
            mostLeft = mostLeft->left;
        }

        pointer->data = mostLeft->data;
        removed = mostLeft;

        if(mostLeftParent->left == mostLeft)
            mostLeftParent->left = nullptr;
        else
            mostLeft -> parent ->right  = mostLeft->right;
    }
    delete removed;
    removed = nullptr;
    return true;
}


template <typename T>
auto BStree::Tree<T>::save(const std::string& filename) -> bool {
    std::ifstream fin(filename.c_str());
    if (!fin.is_open()) {
        std::ofstream fout(filename.c_str());
        fout << *this;
        fout.close();
        return true;
    } else {
        std::string answer;
        std::cout << "\033[0;32mПерезаписать файл? (да, нет)\033[0;34m" << std::endl;
        std::cin >> answer;
        if ((answer == "Да") || (answer == "да") || (answer == "ДА"))  {
            std::ofstream fout(filename.c_str());
            fout << *this;
            fout.close();
            return true;
        } else
            return false;
    }
}

template <typename T>
auto BStree::Tree<T>::load(const std::string& filename) -> bool{
    std::ifstream fin(filename.c_str());
    if (!fin.is_open())
        return false;
    destructor(root);
    T value;
    fin >> value;
    if(!fin)
        return false;
    while(fin) {
        this->add(value);
        fin >> value;
    }
    return true;
}


template <typename T>
auto BStree::Tree<T>::empty() const -> bool {
    if(root == nullptr)
        return false;
    return true;
}
#endif