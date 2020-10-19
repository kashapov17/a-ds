//
// Created by yaroslav on 10/18/20.
//

#ifndef WORK4_HTABLE_H
#define WORK4_HTABLE_H

#include <vector>
#include <fstream>

class htable {

private:
    static int hash(int num);
    void trim();
    int _size;
    struct entry {bool empty; int value;};
    entry* retrieve(int);
    using vec=std::vector<entry>;
    vec *table;
public:

    htable();
    ~htable();
    int capacity() const;
    int size() const;
    int print(std::ostream &);
    void add(int num);
    int remove(int num);
    void load_file(std::ifstream &);
    void clear();

};


#endif //WORK4_HTABLE_H
