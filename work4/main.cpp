#include "htable.h"
#include <iostream>


int main()
{
    std::ifstream in ("/home/yaroslav/repos/a-ds/work4/tests/unbc10.txt", std::ifstream::in);
    htable h;

    char choose=0;
    int num;
    while (choose!='7')
    {
        std::cout << "\navailable functions:\n\tAdd element(1)\n\tRemove element(2)"
                     "\n\tLoad file(3)\n\tPrint table(4)\n\tPrint table stat(5)\n\tClear table(6)\n\tQuit(7)\nchoose: ";
        std::cin >> choose;
        switch (choose) {
            case '1':
                std::cout << "num to add: ";
                std::cin >> num;
                h.add(num);
                break;
            case '2':
                std::cout << "num to remove: ";
                std::cin >> num;
                if(h.remove(num)==-1) std::cout << "element missing...\n";
                break;
            case '3':
                h.load_file(in);
                break;
            case '4':
                if(h.print(std::cout) == 0) std::cout << "table is empty.\n";
                break;
            case '5':
                std::cout << "valid elements: " << h.size() << "\n";
                std::cout << "quantity of entries in hash table (inc empty): " << h.capacity() << "\n";
            case '6':
                h.clear();
                break;
            case '7':
                break;
            default:
                num=0;
                std::cout << "wrong choice.\n";
        }
    }

    std::cout << "god bye!" << std::endl;
    return 0;
}
