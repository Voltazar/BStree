#include <iostream>
#include <locale>
#include "tree.hpp"

auto error() -> void;
int main() {
    std::ofstream fout("answer.txt");
    fout << "Да";
    fout.close();
    setlocale(LC_ALL, "RUS");
    BStree::Tree<int> tree = { 25, 4, 55, 5, 67, -4, 0, 6};
    BStree::Tree<int> tree1;

    std::cout<<"\033[1;33mПример загрузки в файл и из файла бинарного дерева поиска:"<<std::endl
             <<"\033[1;32mИсходное дерево 1:  \033[0;34m"<<std::endl;
    tree.print();

    std::cout<<"\033[0;32mСоздадим пустое дерево 2: ";
    tree1.print();

    std::freopen("answer.txt", "r", stdin);
    
    std::cout<<"\033[0;32mСохраним дерево 1 в файл BStree.txt \033[0;34m"<<std::endl;
    tree.save("BStree.txt");
    std::cout<<"\033[0;32mЗагрузим дерево из файла BStree.txt и присвоим его дереву 2 \033[0;34m"<<std::endl;
    tree1.load("BStree.txt");

    std::cout<<"\033[0;32mВыведем дерево 2:"<<std::endl;
    tree1.print();
    std::cout<<std::endl;
}