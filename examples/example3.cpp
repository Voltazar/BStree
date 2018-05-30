#include <iostream>
#include <locale>
#include "tree.hpp"

auto error() -> void;
int main() {
    setlocale(LC_ALL, "RUS");
    BStree::Tree<int> tree = { 25, 4, 55, 5, 67, -4, 0, 6};

    std::cout<<"\033[1;33mПример добавления узла в бинарное дерево поиска:"<<std::endl
             <<"\033[1;32mИсходное дерево:  \033[0;34m";

    tree.print_order(std::cout, BStree::traversal_order::pre);
    std::cout<<std::endl;

    std::cout<<"\033[0;32mДобавим в дерево 1 узел со значением 100:\033[0;34m"<<std::endl;
    if(!tree.add(100))
        std::cout<<"\033[1;31mУзел уже существует!\033[0;37m\U0001F631\033[0;34m" <<std::endl;

    std::cout<<"\033[0;32mДобавим в дерево 1 узел со значением 25:\033[0;34m"<<std::endl;
    if(!tree.add(25))
        std::cout<<"\033[1;31mУзел уже существует!\033[0;37m\U0001F631\033[0;34m" <<std::endl;


    
    std::cout<<"\033[1;32mВыведем получившееся дерево:   \033[0;34m";
    tree.print_order(std::cout, BStree::traversal_order::pre);
    std::cout<<std::endl;

}



