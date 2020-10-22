/**
 * @brief header for the htable class
 * @file htable.h
 * @author Kashapov Yaroslav
 * @date 2020
*/

#ifndef WORK4_HTABLE_H
#define WORK4_HTABLE_H

#include <list>
#include <vector>
#include <fstream>
#include <iterator>

class htable {
public:
    htable();
    ~htable();
    int capacity() const;
    int size() const;
    int print(std::ostream &);
    void add(int);
    int remove(int);
    void load_file(std::ifstream &, const std::string &);
    void clear();
    int search(int num);

private:
    static int hash(int);
    void trim();
    int _size;
    std::vector<std::list<int>> *table;
    std::list<int>::iterator retrieve(int);
};

#endif //WORK4_HTABLE_H
