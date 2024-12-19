//Требование к программам: 
//Задача 3. Задача на шаблоны
//− Язык программирования - С++, в чистом виде, без расширения типа.net.
//− Программа – консольное приложение с меню, задача не завершается после одной
//итерации(а только при выборе пункта меню «выход»).
//− Ввод - вывод во всех вариантах с клавиатуры и из файла.Имя файла(с расширением)
//запрашивается у пользователя.
//− В коде обязательно условие задачи и автор(в комментариях).
//− Не использовать в данной задаче : auto, лямбда - функции, контейнеры вроде
//std::vector, std::list.
//− Задача не должна падать как при любом вводе, так и при любых действиях
//в консольном меню.
//Требования использования стандарта C++20 :
//    − Пользовательские(написанные вами) модули не состоят из cpp + h, а являются одним
//    файлом(содержащим export - ы) и подключаются с помощью import.
//    − При необходимости перегрузки операторов сравнения использовать трехстороннее
//    сравнение(он же космический корабль или <=> ).
//    − Если есть возможность, использовать цикл вида for (int i : collection)
//    (хоть это и появилось раньше C++20).
//    Общее условие
//    Использование созданного шаблонного класса необходимо показать на трех разных
//    типах данных :
//− Числовой;
//− Строковый;
//− Пользовательская структура на выбор сдающего(минимум 3 поля).
// 9. Реализовать шаблон класса дерево бинарного поиска BinaryTree<X>, хранящий 
//элементы произвольного типа.Класс должен в обязательном порядке содержать
//методы :
//− Вставка элемента в дерево;
//− Удаление элемента из дерева;
//− Поиск элемента;
//− Вычисление высоты дерева и его размера;
//− Печать дерева на консоль;
//− Вывод дерева в файл;
//− инициализация дерева из файла.
// Михайловская 9
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
import BinaryTree;
import Book;

template<typename T>
T get_file();
bool condition(int x, int border);
void read_and_check(int& x, bool(*condition)(int, int), int border);
int menu(const std::string message, bool(*condition)(int, int), int border);
int exit();

template<typename T>
void process();

int valid_int();
std::string valid_string();
int main()
{
    int choice_type{};
    do
    {
        choice_type = menu("Select the type that will store the tree:\n1. int\n2. std::string\n"
            "3. Class Book (fields: Title, Author, year)\n4. Exit\n", condition, 5);
        switch (choice_type)
        {
        case 1:
            process<int>();
            break;
        case 2:
            process<std::string>();
            break;
        case 3:
            process<Book>();
            break;
        default:
            choice_type = exit();
            break;
        }
    } while (choice_type != 4);
    return 0;
}

template<typename T>
T get_file()
{
    std::cout << "Enter the file name:\n>";
    std::string file_name;
    std::cin >> file_name;
    T file(file_name);
    while (!file)
    {
        std::cout << "The file was not found! Enter the correct file name!\n-> ";
        std::cin.clear();
        std::string file_name;
        std::cin >> file_name;
        file.open(file_name);
    }
    return file;
}
bool condition(int x, int border)
{
    return x > 0 && x < border;
}

void read_and_check(int& x, bool(*condition)(int, int), int border)
{
    std::cout << "\n->";
    while (!(std::cin >> x && condition(x, border))) {
        std::cout << "Mistake! Enter the correct value:\n";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "\n->";
    }
}

int menu(const std::string message, bool(*condition)(int, int), int border)
{
    std::cout << message;
    int option{};
    read_and_check(option, condition, border);
    std::cout << "\n";
    return option;
}

int exit()
{
    std::cout << "\nFinish the job? (Y/any key): ";
    char is_exit;
    short option_exit{};
    std::cin >> is_exit;
    if (is_exit == 'Y' || is_exit == 'y')
        option_exit = 4;
    return option_exit;
}
//− Вставка элемента в дерево;
//− Удаление элемента из дерева;
//− Поиск элемента;
//− Вычисление высоты дерева и его размера;
//− Печать дерева на консоль;
//− Вывод дерева в файл;
//− инициализация дерева из файла.
template<typename T>
void process()
{
    BinaryTree<T> tree;
    T tmp;
    int choice{};
    do 
    {
        choice = menu("1. Insert an element into the tree\n2. Remove an element from the tree\n3. Find an element\n"
            "4. Calculate the height of the tree\n5. Calculate the size of the tree\n6. Printing a tree on the screen\n"
            "7. Output a tree to a file\n8. Fill in the tree from the file\n9. Finish working with this type of tree\n"
            , condition, 10);
        switch (choice)
        {
        case 1:
        {
            tmp = validation<T>();
            tree.add(tmp);
            break;
        }
        case 2:
        {
            tmp = validation<T>();
            if (tree.del(tmp))
                std::cout << "The element has been deleted\n";
            else std::cout << "There is no such element in the tree\n";
            break;
        }
        case 3:
        {
            tmp = validation<T>();
            if (tree.find(tmp))
                std::cout << "The tree element is found\n";
            else std::cout << "There is no such element in the tree\n";
            break;
        }
        case 4:
        {
            std::cout << "Height of the tree: " << tree.height() << '\n';
            break;
        }
        case 5:
        {
            std::cout << "Tree Size: " << tree.count_nodes() << '\n';
            break;
        }
        case 6:
        {
            tree.print_to_console();
            break;
        }
        case 7:
        {
            std::ofstream file = get_file<std::ofstream>();
            tree.print_to_file(file);
            break;
        }
        case 8:
        {
            std::ifstream file = get_file<std::ifstream>();
            tree.fill_from_file(file);
            break;
        }
        default:
            break;
        }
    } while (choice != 9);
}

int valid_int()
{
    std::string input;
    int elem;
    bool flag{};
    do
    {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "Enter the element: ";

        std::getline(std::cin, input);

        std::istringstream ss(input);
        if (ss >> elem)
        {
            if (ss.eof()) { flag = true; }
        }
        if (!flag)
        {
            std::cout << "The wrong element has been entered\n";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
        }
    } while (!flag);
    return elem;
}
std::string valid_string()
{
    std::string str;
    std::cout << "Enter the element: ";
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::getline(std::cin, str);
    return str;
}
template<typename T>
T validation()
{
    T tmp;

    if constexpr (std::is_same<T, int>::value)
    {
        tmp = valid_int();
    }

    else if constexpr (std::is_same<T, std::string>::value)
    {
        tmp = valid_string();
    }
    else
    {
        std::cin >> tmp;
        std::cin.ignore(std::cin.rdbuf()->in_avail());
    }
    return tmp;
}