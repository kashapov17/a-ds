#include <vector>
#include <iostream>

#include "bintree.h"
#include "rbtree.h"


template <typename Type, typename Tree>
void tree_fill(std::vector<Type> &v, Tree &t)
{
    for(const auto &it : v)
        t.add(it);
}

int main()
{
    std::ostream &ost(std::cout);

    using type = int;
    std::vector<type> v {1, 32, 45, 5, 10, -1, 2, 4, 22};

    ost << "Binary Tree:\n";
    bintree<type> btree;
    tree_fill(v, btree);
    btree.print(ost);
    ost << "\nall max/2 removed:\n";
    btree.removeLess(btree.max()/2.0);
    btree.print(ost);

    ost << "\nRed-Black Tree: [..] - black, (..) - red\n";
    rbtree<type> rbltree;
    tree_fill(v, rbltree);
    rbltree.print(ost);

    return 0;
}
