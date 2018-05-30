#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "catch.hpp"
#include "tree.hpp"

TEST_CASE("Creating tree") {
    BStree::Tree<int> tree;
    REQUIRE(tree.empty() == false);
    BStree::Tree<int> tree_ = {1};
    REQUIRE(tree_.empty() == true);
}

TEST_CASE("Copy tree") {
    BStree::Tree<int> tree  { 1, 2, 3, 4 };
    BStree::Tree<int> tree1  {tree};

    std::string result = "1  2  3  4  ";
    std::string str;

    std::stringstream out(str);
    out << tree1;

    std::string result_;
    getline(out, result_);

    REQUIRE(result_ == result);

}
TEST_CASE("Printing of tree by various traversal order") {
    BStree::Tree<int> tree  { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
    std::string pre = "8  4  2  1  3  6  5  7  12  10  9  11  14  13  15  ";
    std::string in = "1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  ";
    std::string post = "1  3  2  5  7  6  4  9  11  10  13  15  14  12  8  ";

    std::string str;
    std::stringstream out(str);

    tree.print_order(out, BStree::traversal_order::pre);
    out<<std::endl;
    tree.print_order(out, BStree::traversal_order::in);
    out<<std::endl;
    tree.print_order(out, BStree::traversal_order::post);
    out<<std::endl;

    std::string result_pre;
    std::string result_in;
    std::string result_post;

    getline(out, result_pre);
    getline(out, result_in);
    getline(out, result_post);

    REQUIRE(pre == result_pre);
    REQUIRE(in == result_in);
    REQUIRE(post == result_post);
}

TEST_CASE("Asigment of tree") {
    BStree::Tree<int> tree {1, 2, 3, 4};
    BStree::Tree<int> tree1 {1, 2, 3};

    tree = tree1;

    std::string buffer;
    std::stringstream out(buffer);

    out << tree;

    std::string result = "1  2  3  ";
    std::string res;
    getline(out, res);
    REQUIRE(res == result);
}


TEST_CASE("Adding node") {
    BStree::Tree<int> tree  { 25, 34, 12, 4, 7, 67, 78, 9, 0 };

    tree.add(1);
    tree.add(20);
    tree.add(5);


    std::string str;
    std::stringstream out(str);

    tree.print_order(out, BStree::traversal_order::pre);

    std::string result = "25  12  4  0  1  7  5  9  20  34  67  78  ";
    std::string result_of_adding;
    getline(out, result_of_adding);
    REQUIRE(tree.add(25) == false);
    REQUIRE(tree.add(100) == true);
    REQUIRE(result== result_of_adding);
}


TEST_CASE("Deleting node") {
    BStree::Tree<int> tree  {8, 4, 12, 2, 6, 10, 14, 1, 3, 5,7, 9, 11, 13, 15 };
    tree.remove(4);
    tree.remove(1);
    tree.remove(9);
    tree.remove(8);
    tree.remove(14);
    tree.remove(2);
    tree.remove(3);

    BStree::Tree<int> tree1 {1};

    REQUIRE(tree.remove(15) == true);
    REQUIRE(tree1.remove(1) == true);
    REQUIRE(tree.remove(100) == false);
    REQUIRE(tree.remove(13) == true);
}

TEST_CASE("Input in file") {
    BStree::Tree<int> tree  { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };

    std::string text = "8  4  2  1  3  6  5  7  12  10  9  11  14  13  15  ";
    std::string buffer;
    std::stringstream out (buffer);

    out<<tree;

    std::string result;
    getline(out, result);

    REQUIRE(result == text);
}

TEST_CASE("Existence of node") {
    BStree::Tree<int> tree  { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
    REQUIRE(tree.search(8) == true);
    REQUIRE(tree.search(100) == false);
}

TEST_CASE("Saving on file") {
    BStree::Tree<int> tree  { 5, 2, 6, 8};

    std::ofstream fout("answer.txt");
    fout <<"Да"<<std::endl<<"Нет";
    fout.close();

    std::freopen("answer.txt", "r", stdin);

    tree.save("BStree.txt");
    REQUIRE( tree.save("BStree.txt") == true);
    REQUIRE( tree.save("BStree.txt") == false);
}

TEST_CASE("Loading from file") {
    std::string buffer;
    std::stringstream out (buffer);
    std::string result_ = "1  2  3  4  5  ";

    BStree::Tree<int> tree {1, 2, 3, 4,5};
    tree.save("Tree.txt");

    BStree::Tree<int> tree1;
    BStree::Tree<int> tree2;

    tree1.load("Tree.txt");

    out << tree1;
    std::string result;
    getline(out,result);
    std::ofstream fout("t.txt");
    fout<<"a3";
    fout.close();

    REQUIRE( result_ == result);
    REQUIRE( tree.load("List.txt") == false);
    REQUIRE( tree2.load("t.txt") == false);
}

TEST_CASE("Swap") {
    BStree::Tree<int> tree{1, 2, 3,4};
    BStree::Tree<int> tree1{4, 3, 2, 1};

    tree.swap(tree1);

    std::string buffer;
    std::stringstream out (buffer);
    std::string result_ = "4  3  2  1  1  2  3  4  ";

    out << tree;
    out << tree1;
    std::string result;
    getline(out, result);
    REQUIRE(result == result_);
}

TEST_CASE("Iterator") {
    BStree::Tree<int> tree{8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};

    std::string pre_result ="1 2 3 4 5 6 7 8 9 10 11 12 13 14 15";
    std::string post_result ="15 14 13 12 11 10 9 8 7 6 5 4 3 2 1";

    std::string buffer;
    std::stringstream out (buffer);

    BStree::BSTIterator<int> it_ = tree.begin();

    REQUIRE(*it_ == 1);

    for (; it_ != tree.end(); ++it_) {
        out << *it_ << " ";
    }
    out<<*it_<<std::endl;

    REQUIRE(*it_ == 15);

    BStree::BSTIterator<int> it = tree.rbegin();

    REQUIRE(*it == 15);

    for (; it != tree.rend(); --it) {
        out << *it << " ";
    }
    out <<*it<<std::endl;

    REQUIRE(*it == 1);

    std::string result_pre;
    getline(out, result_pre);

    std::string result_post;
    getline(out, result_post);

    REQUIRE(result_pre == pre_result);
    REQUIRE(result_post == post_result);

    BStree::BSTIterator<int> t;
    t = it;
    REQUIRE(*t == *it);
    t++;
    REQUIRE( *t== *it+1);
    t--;
    REQUIRE(*t == *it);

    swap(t, it_);
    REQUIRE(*t == 15);

    t=it;
    REQUIRE((t==it) == true);
    t++;
    REQUIRE((t==it) == false);
}
