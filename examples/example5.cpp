#include <iostream>
#include <locale>
#include <tree.hpp>

int main() {
    setlocale(LC_ALL, "RUS");
    BStree::Tree<int> tree{8, 4, 12, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    std::cout << "Выведем исходное дерево:"<<std::endl;
    tree.print_order(std::cout, BStree::traversal_order::pre);
    
    std::cout<<std::endl << "Выведем дерево, используя итератор прямого обхода: ";
    BStree::BSTIterator<int> it_ = tree.begin();
    for (; it_ != tree.end(); ++it_) {
        std::cout << *it_ << " ";
    }
    std::cout<<*it_;

    std::cout<<std::endl << "Выведем дерево, используя итератор обратного обхода: ";
    BStree::BSTIterator<int> it = tree.rbegin();
    for (; it != tree.rend(); --it) {
        std::cout << *it << " ";
    }
    std::cout <<*it<<std::endl;
    
    std::cout << "Присвоим значение итератора обратного обхода новому итератору t: "<<std::endl;
    BStree::BSTIterator<int> t;
    t = it;
    std::cout<<*t<<std::endl;
    

    std::cout << "Используя swap поменяем итератор прямого обхода с итератором t:"<<std::endl;
    swap(t, it_);

    std::cout<<*t<<std::endl;


}

