#include <iostream>
#include <locale>
#include "tree.hpp"

auto error() -> void;
int main() {
    setlocale(LC_ALL, "RUS");
    BStree::Tree<int> tree = { 25, 4, 55, 5, 67, -4, 0, 6};
    BStree::Tree<int> tree1;


    std::cout<<"\033[0;32mСоздадим и выведем дерево 1 с элементами 25 4 55 5 67 -4 0 6:\033[0;34m"<<std::endl;
    tree.print();
    std::cout<<std::endl;
    std::cout<<"\033[0;32mСоздадим пустое дерево 2 и выведем его:\033[0;34m"<<std::endl;
    tree1.print();
    std::cout<<std::endl;

    std::cout<<"\033[0;32mВыведем дерево 1 прямым обходом: \033[0;34m "<<std::endl;
    tree.print_order(std::cout, BStree::traversal_order::pre);
    std::cout<<std::endl;
    std::cout<<"\033[0;32mВыведем дерево 1  обходом : \033[0;34m "<<std::endl;
    tree.print_order(std::cout, BStree::traversal_order::in);
    std::cout<<std::endl;
    std::cout<<"\033[0;32mВыведем дерево 1  обходом :\033[0;34m"<<std::endl;
    tree.print_order(std::cout, BStree::traversal_order::post);
    std::cout<<std::endl;

    std::cout<<"\033[0;32mДобавим в дерево 1 узел со значением 100:\033[0;34m"<<std::endl;
    if(!tree.add(100))
        std::cout<<"\033[1;31mУзел уже существует!\033[0;37m\U0001F631\033[0;34m" <<std::endl;



    std::cout<<"\033[0;32mДобавим в дерево 1 узел со значением 25:\033[0;34m"<<std::endl;
    if(!tree.add(25))
        std::cout<<"\033[1;31mУзел уже существует!\033[0;37m\U0001F631\033[0;34m" <<std::endl;



    std::cout<<"\033[0;32mУдалим из дерева 1 узел со значением 25:\033[0;34m"<<std::endl;
    if(!tree.remove(25))
        std::cout<<"\033[1;31mУзел не найден!\033[1;37m\U0001F647\033[0;34m" <<std::endl;



    std::cout<<"\033[0;32mУдалим из дерева 1 узел со значением 1:\033[0;34m"<<std::endl;
    if(!tree.remove(1))
        std::cout<<"\033[1;31mУзел  не найден!\033[1;37m\U0001F647\033[0;34m" <<std::endl;



    std::cout<<"\033[0;32mВыведем дерево 1:"<<std::endl;
    tree.print();
    std::cout<<std::endl;



    std::cout<<"\033[0;32mДобавим в дерево 2 узел со значением 99:\033[0;34m"<<std::endl;
    if(!tree1.add(99))
        std::cout<<"\033[1;31mУзел уже существует!\033[0;37m\U0001F631\033[0;34m" <<std::endl;



    std::cout<<"\033[0;32mВыведем дерево 2:"<<std::endl;
    tree1.print();
    std::cout<<std::endl;



    std::cout<<"\033[0;32mУдалим из дерева 2 узел со значением 99:\033[0;34m"<<std::endl;
    if(!tree1.remove(99))
        std::cout<<"\033[1;31mУзел  не найден!\033[1;37m\U0001F647\033[0;34m" <<std::endl;



    std::cout<<"\033[0;32mВыведем дерево 2:"<<std::endl;
    tree1.print();
    std::cout<<std::endl;


    std::ofstream fout("answer.txt");
    fout << "Да";
    fout.close();

    std::freopen("answer.txt", "r", stdin);
    
    std::cout<<"\033[0;32mСохраним дерево 1 в файл BStree.txt \033[0;34m"<<std::endl;
    tree.save("BStree.txt");
    std::cout<<"\033[0;32mЗагрузим дерево из файла BStree.txt и присвоим его дереву 2 \033[0;34m"<<std::endl;
    tree1.load("BStree.txt");
    std::cout<<"\033[0;32mВыведем дерево 2:"<<std::endl;

    tree1.print();
    std::cout<<std::endl;


    std::cout<<"\033[0;32mНайдем в дереве 1 узел со значением 100:\033[0;34m"<<std::endl;
    if(!tree.search(100))
        std::cout<<"\033[1;31mУзел не найден!\033[1;37m\U0001F647\033[0;34m" <<std::endl;
    else
        std::cout<<"\033[1;35mУзел найден!\033[1;37m\U0001F483\033[0;34m" <<std::endl;



    std::cout<<"\033[0;32mНайдем в дереве 1 узел со значением 10000:\033[0;34m "<<std::endl;
    if(!tree.search(10000))
        std::cout<<"\033[1;31mУзел не найден!\033[1;37m\U0001F647\033[0;34m" <<std::endl;
    else
        std::cout<<"\033[1;35mУзел найден!\033[1;37m\U0001F483\033[0;34m" <<std::endl;



    return 0;
}