#ifndef WORK6_BINTREE_H
#define WORK6_BINTREE_H

#include <iostream>

template <typename T>
class bintree {

    struct node
            {
                T val;
                node *l;
                node *r;
            };
    node *root;
    static node *node_alloc(T &);
    void add(T &, node* &);
    node *remove(T &, node *&);
    void removeLess(T &, node *&);
    node *search(T &, node *&);
    node *min(node *);
    node *max(node *);
    void print(const std::string& prefix, const node* n, bool isLeft, std::ostream &ost);
    uint64_t size;


public:
    bintree();
    ~bintree();
    void add(T);
    void print(std::ostream &ost);
    void removeLess(T);
    bool remove(T);
    bool search(T);
    T min();
    T max();
};


#endif //WORK6_BINTREE_H
