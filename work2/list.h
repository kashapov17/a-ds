//
// Created by yaroslav on 18.09.2020.
//

#include <cstdint>
#include <string>

#ifndef WORK2_LIST_H
#define WORK2_LIST_H
namespace node
{
    struct node
    {
        int32_t val;
        node *prev;
        node *next;
    };
}

class list
{
public:
    list();
    ~list();
    void push_back(int32_t val);
    void remove(uint64_t idx);
    uint32_t size() const;
    int32_t& operator[](uint64_t idx);
    bool isEmpty();
    std::string typeName();


private:
    uint64_t _size;
    node::node *last;
    node::node *first;
    node::node *inode(uint64_t idx);
};

#endif //WORK2_LIST_H