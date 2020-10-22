/**
 * @brief work4. Search algorithms
 * @file main.cpp
 * @author Kashapov Yaroslav
 * @date 2020
*/

#include "htable.h"
#include <iostream>

int main()
{
    std::ifstream in;
    htable h;

    char choose=0;
    int num;
    while (choose!='8')
    {
        std::cout << "\navailable functions:\n\tSearch(1)\n\tAdd element(2)\n\tRemove element(3)"
                     "\n\tLoad file(4)\n\tPrint table(5)\n\tPrint table stat(6)\n\tClear table(7)\n\tQuit(8)\nchoose: ";
        std::cin >> choose;
        switch (choose) {
            case '1':
                std::cout << "num to search: ";
                std::cin >> num;
                if (h.search(num) == num) std::cout << "found " << num << "\n";
                else std::cout << "found nothing" << "\n";
                break;
            case '2':
                std::cout << "num to add: ";
                std::cin >> num;
                h.add(int(num));
                break;
            case '3':
                std::cout << "num to remove: ";
                std::cin >> num;
                if(h.remove(num)==-1) std::cout << "element missing...\n";
                break;
            case '4':
                h.load_file(in, "/home/yaroslav/repos/a-ds/work4/tests/unbc10.txt");
                break;
            case '5':
                if(!h.print(std::cout)) std::cout << "table is empty.\n";
                break;
            case '6':
                std::cout << "valid elements: " << h.size() << "\n";
                std::cout << "quantity of entries in hash table (inc empty): " << h.capacity() << std::endl;
                break;
            case '7':
                h.clear();
                break;
            case '8':
                break;
            default:
                num=0;
                std::cout << "wrong choice.\n";
        }
    }

    std::cout << "god bye!" << std::endl;
    return 0;
}
