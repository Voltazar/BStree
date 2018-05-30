/*#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "tree.hpp"

BStree::Tree::Tree(std::initializer_list<int> list) {
    root = nullptr;
    for (auto x: list ) {
        this->add(x);
    }
}

BStree::Tree::Tree(const Tree& tree) : Tree{} {
    std::string str;
    std::stringstream out(str);
    out << tree;
    int value;
    while(out) {
        out >> value;
        this->add(value);
    }
}

auto BStree::Tree::search(int value) const -> bool {
    if(root == nullptr)
        return false;
    Node* node = root;
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

auto BStree::Tree::add(int value) -> bool {
    if(search(value))
        return false;
    if (root == nullptr) {
        root = new Node {value};
        return true;
    }
    Node* node = root;
    while(node != nullptr) {
        if(node->data > value ) {
            if(node -> left == nullptr) {
                node -> left = new Node {value};
                return true;
            }
            node = node -> left;
        } else {

            if(node -> right == nullptr) {
                node -> right = new Node {value};
                return true;
            }
            node = node -> right;

        }
    }
}

auto BStree::Tree::print() -> void {
    if(root == nullptr) {
        std::cout <<"\033[1;31mДерево пусто!\033[0;37m\U0001F631\033[0;34m" <<std::endl;
        return;
    }
    print_root(root);
}

auto BStree::Tree::print_root(const Node* node ) -> void {
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

auto print_pre(std::ostream& out, const BStree::Node* node) -> std::ostream& {
    if(node != nullptr) {
        out << node->data<<"  ";
        print_pre(out, node->left);
        print_pre(out, node->right);
    }
    return out;
}

auto print_in(std::ostream& out, const BStree::Node* node)-> std::ostream& {
    if(node != nullptr) {
        print_in(out,node->left);
        out << node->data<<"  ";
        print_in(out,node->right);
    }
    return out;
}

auto print_post(std::ostream& out, const BStree::Node* node)  -> std::ostream& {
    if(node != nullptr) {
        print_post(out,node->left);
        print_post(out,node->right);
        out << node->data<<"  ";
    }
    return out;
}


auto BStree::Tree::print_order(std::ostream& out, BStree::traversal_order order) const  -> std::ostream& {
    if(order == traversal_order::pre) {
        print_pre(out,root);
    } else if (order == traversal_order::in) {
        print_in(out,root);
    } else {
        print_post(out,root);
    }
    return out;
}

auto BStree::Tree::swap(Tree& tree) -> void {
    std::swap(root, tree.root);
}

auto BStree::Tree::destructor(Node* node) -> void {
    if(node != nullptr) {
        destructor(node->left);
        destructor(node->right);
        delete node;
    }
}

auto BStree::Tree::remove(int value)-> bool{
    if(!search(value))
        return false;
    Node* pointer = root;
    Node* parent  = nullptr;

    while( pointer->data != value) {
        parent = pointer;
        if(value < pointer->data)
            pointer = pointer->left;
        else
            pointer = pointer->right;
    }

    Node* removed = nullptr;

    if (pointer->left == nullptr || pointer->right == nullptr) {
        Node* child = nullptr;
        removed = pointer;

        if(pointer->left != nullptr)
            child = pointer->left;
        else if(pointer->right != nullptr)
            child = pointer->right;

        if(parent == nullptr)
            root = child;
        else {
            if(parent->left == pointer)
                parent->left = child;
            else
                parent->right = child;
        }
    } else {
        Node* mostLeft = pointer->right;
        Node* mostLeftParent = pointer;

        while (mostLeft->left != nullptr) {
            mostLeftParent = mostLeft;
            mostLeft = mostLeft->left;
        }

        pointer->data = mostLeft->data;
        removed = mostLeft;

        if(mostLeftParent->left == mostLeft)
            mostLeftParent->left = nullptr;
        else
            mostLeftParent->right = mostLeft->right;
    }
    delete removed;
    removed = nullptr;
    return true;
}

auto BStree::Tree::save(const std::string& filename) -> bool {
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

auto BStree::Tree::operator=(const Tree& tree) -> Tree& {
    destructor(root);
    Tree tmp{tree};
    this->swap(tmp);
    return *this;
}

auto BStree::Tree::load(const std::string& filename) -> bool{
    std::ifstream fin(filename.c_str());
    if (!fin.is_open())
        return false;
    destructor(root);
    int value;
    fin >> value;
    if(!fin)
        return false;
    while(fin) {
        this->add(value);
        fin >> value;
    }
    return true;
}

auto showmenu() -> void {
    std::cout<<"\033[1;32mВыберите одну из операций:\033[0;34m"<<std::endl
    <<"1. Вывести дерево на экран"<<std::endl
    <<"2. Вывести список узлов дерева"<<std::endl
    <<"3. Добавить узел в дерево"<<std::endl
    <<"4. Удалить узел из дерева"<<std::endl
    <<"5. Сохранить дерево в файл"<<std::endl
    <<"6. Загрузить дерево из файла"<<std::endl
    <<"7. Проверить наличие узла"<<std::endl
    <<"8. Завершить работу программы"<<std::endl;
}

auto BStree::Tree::empty() const -> bool {
    if(root == nullptr)
        return false;
    return true;
}

auto error() -> void {
    std::cin.clear();
    while (std::cin.get() != '\n');
    std::cout << "\033[1;31mВведено некорректное значение!\033[0;37m\U0001F631" << std::endl;
}
*/