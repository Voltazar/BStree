#include <iostream>
#include <locale>
#include <string>
#include "tree.hpp"

auto showmenu() -> void;
auto error() -> void;
int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RUS");
    BStree::Tree<int> tree;
    if(argc == 2 ) {
        tree.add(atoi(argv[1]));

    } else if(argc >2 ) {
        for (int i = 1; i < argc ; i++) {
            tree.add(atoi(argv[i]));
        }
    }

    bool flag = false;

    for(;;) {
        if(flag) break;
        showmenu();
        int count;
        std::cin >> count;
        while (!std::cin) {
            error();
            std::cout << "\033[0;32mПовторите ввод\033[1;37m \U0001F58E \033[0;32m:\033[0;34m";
            std::cin >> count;
        }
        if(!tree.empty() && count !=3 && count !=6 && count !=8) count = 0;
        switch (count) {

        case 0:
            std::cout <<"\033[1;31mДерево пусто!\033[0;37m\U0001F631\033[0;34m" <<std::endl;
            break;

        case 1:
            tree.print();
            break;

        case 2: {
            std::cout<<"\033[0;32mВыберите вариант обхода: \033[0;34m"<<std::endl
                     <<"a. Прямой обход"<<std::endl
                     <<"b. Поперечный обход"<<std::endl
                     <<"c. Обратный обзод"<<std::endl;
            char choice;
            std::cin >> choice;
            switch(choice) {

            case 'a': {
                tree.print_order(std::cout, BStree::traversal_order::pre );
                std::cout << std::endl;
            }
            break;

            case 'b': {
                tree.print_order(std::cout, BStree::traversal_order::in);
                std::cout << std::endl;
            }
            break;

            case 'c':  {
                tree.print_order(std::cout, BStree::traversal_order::post);
                std::cout << std::endl;
            }
            break;

            default:
                std::cout << "\033[1;31mОбход не найден!\033[0;37m\U0001F631" << std::endl;
                break;
            }
        }
        break;

        case 3: {
            std::cout<<"\033[0;32mВведите значение для нового узла: \033[0;34m";
            int value;
            std::cin >> value;
            while (!std::cin) {
                error();
                std::cout << "\033[0;32mПовторите ввод: \033[1;37m \U0001F58E \033[0;32m:\033[0;34m";
                std::cin >> value;
            }
            if(!tree.add(value))
                std::cout<<"\033[1;31mУзел "<<value<<" уже существует!\033[0;37m\U0001F631\033[0;34m" <<std::endl;
        }
        break;

        case 4: {
            std::cout<<"\033[0;32mВведите значение для удаляемого узла: \033[0;34m";
            int value;
            std::cin >> value;
            while (!std::cin) {
                error();
                std::cout << "\033[0;32mПовторите ввод: \033[1;37m \U0001F58E \033[0;32m:\033[0;34m";
                std::cin >> value;
            }
            if(!tree.remove(value))
                std::cout<<"\033[1;31mУзел "<<value<<" не найден!\033[1;37m\U0001F647\033[0;34m" <<std::endl;
        }
        break;

        case 5: {
            std::string filename;
            std::cout <<"\033[0;32mУкажите путь к файлу: \033[0;34m";
            std::cin >> filename;
            if(!tree.save(filename))
                std::cout<<"\033[0;32mФайл не изменен\033[0;34m"<<std::endl;
            else
                std::cout<<"\033[0;32mДерево сохранено\033[0;34m"<<std::endl;
        }
        break;

        case 6: {
            std::string filename;
            std::cout <<"\033[0;32mУкажите путь к файлу: \033[0;34m";
            std::cin >> filename;
            if(!tree.load(filename))
                std::cout<<"\033[1;31mФайл не найден\033[1;37m\U0001F647\033[0;34m"<<std::endl;
        }
        break;

        case 7: {
            std::cout<<"\033[0;32mВведите значение для поиска: \033[0;34m";
            int value;
            std::cin >> value;
            while (!std::cin) {
                error();
                std::cout << "\033[0;32mПовторите ввод: \033[1;37m \U0001F58E \033[0;32m:\033[0;34m";
                std::cin >> value;
            }
            if(!tree.search(value))
                std::cout<<"\033[1;31mУзел не найден!\033[1;37m\U0001F647\033[0;34m" <<std::endl;
            else
                std::cout<<"\033[1;35mУзел найден!\033[1;37m\U0001F483\033[0;34m" <<std::endl;
        }

        break;

        case 8: {
            std::string  Answer;
            std::cout <<"\033[1;31mВы хотите выйти из программы ?(Да/Нет)\033[0;34m " << std::endl;
            std::cin >> Answer;
            if ((Answer == "Да") || (Answer == "да") || (Answer == "ДА")) {
                std::cout <<"\033[1;32mДо свидания!"<< std::endl;
                flag = true;
            } else if ((Answer == "НЕТ") || (Answer == "нет") || (Answer == "Нет"))
                break;
            else
                error();
        }
        break;

        default:
            std::cout << "\033[1;31mОперация не найдена!\033[0;37m\U0001F631" << std::endl;
            break;

        }
    }
    return 0;
}


auto error() -> void {
    std::cin.clear();
    while (std::cin.get() != '\n');
    std::cout << "\033[1;31mВведено некорректное значение!\033[0;37m\U0001F631" << std::endl;
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