#include <iostream>
#include <locale>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cmath>
#include "tree.hpp"


int main() {
    setlocale(LC_ALL, "RUS");
    std::ofstream out("answer.txt");
    out<<"Да";
    out.close();
    std::freopen("tree_bench.txt", "w", stdout);
    std::ofstream fout("bench.txt");
    clock_t  t_start;
    clock_t  t_end;
    for (size_t exp = 1; exp <= 9;  exp ++ ) {
        int value;
        BStree::Tree<int> tree;
        for(size_t num_el = 1; num_el <= pow(10,exp); num_el++) {
            value  = rand();
            while(!tree.add(value)) {
                value = rand();
                tree.add(value);
            }

        }
        std::freopen("answer.txt", "r", stdin);
        fout<<"Adding:"<<std::endl;
        value = rand();
        t_start = clock();
        tree.add(value);
        t_end= clock() - t_start;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;

        fout<<"Removing:"<<std::endl;
        t_start = clock();
        tree.remove(value);
        t_end= clock() - t_start;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;

        fout<<"Existing:"<<std::endl;
        t_start = clock();
        tree.search(value);
        t_end= clock() - t_start;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;

        fout<<"Print:"<<std::endl;
        t_start = clock();
        tree.print();
        t_end= clock() - t_start;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;

        fout<<"Print pre order:"<<std::endl;
        t_start = clock();
        tree.print_order(std::cout, BStree::traversal_order::pre);
        t_end= clock() - t_start;
        std::cout<<std::endl;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;

        fout<<"Print in order:"<<std::endl;
        t_start = clock();
        tree.print_order(std::cout, BStree::traversal_order::in);
        t_end = clock() - t_start;
        std::cout<<std::endl;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;

        fout<<"Print post order:"<<std::endl;
        t_start = clock();
        tree.print_order(std::cout, BStree::traversal_order::post);
        std::cout<<std::endl;
        t_end = clock() - t_start;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;

        fout<<"Save in file:"<<std::endl;
        t_start = clock();
        tree.save("BStree.txt");
        t_end = clock() - t_start;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;

        fout<<"Load from file:"<<std::endl;
        t_start = clock();
        tree.load("BStree.txt");
        t_end = clock() - t_start;
        fout<<"10^"<<exp<<" : "<<(float)t_end/CLOCKS_PER_SEC<<std::endl;
    }
}












