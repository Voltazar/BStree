#include <iostream>
#include <locale>
#include "tree.hpp"

auto error() -> void;
int main() {
    setlocale(LC_ALL, "RUS");
    BStree::Tree<int> tree = { 25, 4, 55, 5, 67, -4, 0, 6};

    std::cout<<"\033[1;33mПример вывода бинарного дерево поиска различными обходами:"<<std::endl;

    std::cout<<"\033[0;32mВыведем дерево 1 прямым обходом: \033[0;34m "<<std::endl;
    tree.print_order(std::cout, BStree::traversal_order::pre);
    std::cout<<std::endl;
    std::cout<<"\033[0;32mВыведем дерево 1 поперечным обходом : \033[0;34m "<<std::endl;
    tree.print_order(std::cout, BStree::traversal_order::in);
    std::cout<<std::endl;
    std::cout<<"\033[0;32mВыведем дерево 1 обратным обходом :\033[0;34m"<<std::endl;
    tree.print_order(std::cout, BStree::traversal_order::post);
    std::cout<<std::endl;
}