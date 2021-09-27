#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include "Timer.h"

/*
    –еализуйте шаблонную функцию Swap, котора€ принимает два указател€ и обменивает местами значени€, на которые указывают эти указатели.
*/
template<typename T>
void Swap(T* a, T* b)
{

    std::cout << "Before: " << std::endl;
    std::cout << a << " = " << *a << std::endl;
    std::cout << b << " = " << *b << std::endl;

    T tmp{ *a };
    *a = *b;
    std::cout << "Transfer 'a' to tmp and 'b' to 'a':" << std::endl;

    std::cout << "tmp" << " = " << tmp << std::endl;
    std::cout << a << " = " << *a << std::endl;
    std::cout << b << " = " << *b << std::endl;

    *b = tmp;

    std::cout << "Transfer 'tmp' to 'b'" << std::endl;

    std::cout << "tmp" << " = " << tmp << std::endl;
    std::cout << a << " = " << *a << std::endl;
    std::cout << b << " = " << *b << std::endl;
}
/*
    –еализуйте шаблонную функцию SortPointers, котора€ принимает вектор указателей и сортирует указатели по значени€м, на которые они указывают.
*/
template<typename T>
void SortPointers(std::vector<T*> &list)
{
    Timer t("Sort:");
    std::sort(list.begin(), list.end(), [](const int* a, const int* b) { return *a < *b; });
    t.print();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    std::cout << "Exercise 1:" << std::endl;
    std::string* a = new std::string("A");
    std::string* b = new std::string("B");

    Swap(a, b);

    delete a;
    delete b;

    std::cout << std::endl;
    std::cout << "Exercise 2:" << std::endl;
    srand(static_cast<unsigned int>(time(0)));
    std::vector<int*> list;

    std::cout << "Before: " << std::endl;

    for (size_t i = 0; i < 10; i++)
    {
        list.push_back(new int(rand()));
        std::cout << *list.at(i) << " ";
    }

    std::cout << std::endl;

    SortPointers(list);

    std::cout << "After: " << std::endl;
    for (int* val : list)
        std::cout << *val << " ";

    std::cout << std::endl;

    /*   ѕодсчитайте количество гласных букв в книге У¬ойна и мирФ.ƒл€ подсчета используйте 4 способа:
       - count_if и find
       - count_if и цикл for
       - цикл for и find
       - 2 цикла for
       «амерьте врем€ каждого способа подсчета и сделайте выводы.

       —правка:
       count_if - это алгоритмическа€ функци€ из STL, котора€ принимает 3 параметра: итератор на начало, итератор на конец и унарный предикат (функцию, принимающую один параметр и возвращающую тип bool).
       find - это метод класса string, который возвращает позицию символа (строки), переданного в качестве параметра, в исходной строке. ≈сли символ не найден, то метод возвращает string::npos.
   */

    std::cout << std::endl;
    std::cout << "Exercise 3:" << std::endl;

    std::ifstream file1("Input.txt");

    if (file1.is_open())
    {
        Timer t("Speed");

        std::string line;
        std::string vowels = "аоиеЄэыую€";
        size_t x{};

        while (std::getline(file1, line))
            x += std::count_if(line.begin(), line.end(), [vowels](const char c) { return vowels.find(c) != std::string::npos; });

        std::cout << "count_if и find = " << x << " vowels symbols. ";
        t.print();
        file1.close();
    }

    std::ifstream file2("Input.txt");

    if (file2.is_open())
    {
        Timer t("Speed");

        std::string line;
        std::string vowels = "аоиеЄэыую€";
        size_t x{};

        while (std::getline(file2, line))
        {
            x += std::count_if(line.begin(), line.end(), [vowels](const char c) {

                for (size_t i = 0; i < vowels.length(); i++)
                    if (vowels[i] == c)
                        return true;

                return false;
            });
        }

        std::cout << "count_if и цикл for = " << x << " vowels symbols. ";
        t.print();
        file2.close();
    }

    std::ifstream file3("Input.txt");

    if (file3.is_open())
    {
        Timer t("Speed");

        std::string line;
        std::string vowels = "аоиеЄэыую€";
        size_t x{};

        while (std::getline(file3, line))
        {
            for (size_t i = 0; i < line.length(); i++)
                if (vowels.find(line[i]) != std::string::npos)
                    x++;
        }

        std::cout << "цикл for и find = " << x << " vowels symbols. ";
        t.print();
        file3.close();
    }

    std::ifstream file4("Input.txt");

    if (file4.is_open())
    {
        Timer t("Speed");

        std::string line;
        std::string vowels = "аоиеЄэыую€";
        size_t x{};
        
        while (std::getline(file4, line))
        {
            for (size_t i = 0; i < line.length(); i++)
            {
                for (size_t z = 0; z < vowels.length(); z++)
                {
                    if (line[i] == vowels[z])
                    {
                        x++;
                        break;
                    }
                }
            }
        }

        std::cout << "2 цикла for = " << x << " vowels symbols. ";
        t.print();
        file4.close();
    }

    return 0;
}