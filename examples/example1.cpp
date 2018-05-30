#include <iostream>
#include <locale>
#include "tree.hpp"

auto error() -> void;
int main() {
    setlocale(LC_ALL, "RUS");
    BStree::Tree<int> tree = { 25, 4, 55, 5, 67, -4, 0, 6};
    BStree::Tree<int> tree1;
    std::cout<<"\033[1;33mПример создания бинарного дерево поиска и его вывода:"<<std::endl;

    std::cout<<"\033[0;32mСоздадим и выведем дерево 1 с элементами 25 4 55 5 67 -4 0 6:\033[0;34m"<<std::endl;
    tree.print();
    std::cout<<std::endl;
    std::cout<<"\033[0;32mСоздадим пустое дерево 2 и выведем его:\033[0;34m"<<std::endl;
    tree1.print();
    std::cout<<std::endl;
}