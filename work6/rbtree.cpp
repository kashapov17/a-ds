#include <cstdint>
#include "rbtree.h"

template <typename T>
rbtree<T>::rbtree()
{
    size=0;
    root = nullptr;
}

template<typename T>
rbtree<T>::~rbtree()
{
    destroy(root);
    root = nullptr;
}

template <typename T>
void rbtree<T>::add(T val)
{
    auto n = add(val, root);
    fix_addition(n);
}

template<typename T>
typename rbtree<T>::node *rbtree<T>::add(T &val, rbtree::node *&n)
{
    node *ret = nullptr;
    if (n == nullptr)
    {
        n = node_alloc(val);
        if (root == n)
        {
            n->c = color::BLACK;
            n->p = nullptr;
        }
        return n;
    }
    else if (val < n->val) {
        ret = add(val, n->l);
        n->l->p = n;
    }
    else if (val > n->val) {
        ret = add(val, n->r);
        n->r->p = n;
    }
    return ret;
}

template<typename T>
void rbtree<T>::fix_addition(node *&n)
{
    while (n != root && n->p->c == RED)
    {
        auto parent = n->p;
        node *gparent = n->p->p;
        if (parent == gparent->l) // father is left child
        {
            auto u = gparent->r;
            if (u != nullptr && u->c == RED) {
                color_flip(gparent);
                n = gparent;
            }
            else
                {
                    if (n == parent->r)
                    {
                        leftRotate(parent);
                        n = parent;
                        parent = n->p;
                    }
                    rightRotate(gparent);
                    std::swap(parent->c, gparent->c);
                    n = parent;
                }
        }
        else // father is right child
            {
                auto u = gparent->l;
                if (u != nullptr && u->c == RED) {
                    color_flip(gparent);
                    n = gparent;
                }
                else
                    {
                        if (n == parent->l)
                        {
                            rightRotate(parent);
                            n = parent;
                            parent = n->p;
                        }
                        leftRotate(gparent);
                        std::swap(parent->c, gparent->c);
                        n = parent;
                    }
            }
        //fix_addition(u->p);
    }
    root->c = BLACK;
}

template<typename T>
void rbtree<T>::color_flip(node *&n)
{
    if (n->c == RED)
    {
        n->c = BLACK;
        n->l->c = n->r->c = RED;
    }
    else
        {
            n->c = RED;
            n->l->c = n->r->c = BLACK;
        }
}

template<typename T>
bool rbtree<T>::remove(T val)
{
    return static_cast<bool>(remove(val, root));
}

template<typename T>
typename rbtree<T>::node *rbtree<T>::remove(T &val, rbtree::node *&n)
{
    auto ret = n;
    if (n == nullptr)
        return nullptr;
    if (val < n->val)
        ret = remove(val, n->l);
    else if (val > n->val)
        ret = remove(val, n->r);
    else
    {
        auto old_n = n;
        if(n->l == nullptr)
        {
            n = n->r;
            delete old_n;
            size--;
        }
        else if (n->r == nullptr)
        {
            n = n->l;
            delete old_n;
            size--;
        }
        else
        {
            auto min_n = min(n->r);
            n->val = min_n->val;
            remove(min_n->val, n->r);
        }
    }
    return ret;
}

template<typename T>
void rbtree<T>::fix_removing(rbtree::node *&)
{

}

template<typename T>
inline typename rbtree<T>::node* rbtree<T>::node_alloc(T &val, color c)
{
    node *n = new node;
    n->c = c;
    n->val = val;
    n->l = n->r = nullptr;
    return n;
}

template<typename T>
void rbtree<T>::destroy(node *&n)
{
    if (n == nullptr)
        return;
    destroy(n->l);
    destroy(n->r);
    delete n;
}

template<typename T>
void rbtree<T>::removeLess(T val)
{
    removeLess(val, root);
}

template<typename T>
void rbtree<T>::removeLess(T &val, rbtree::node *&n)
{
    if (n == nullptr) return;
    if (n->val >= val)
        removeLess(val, n->l);
    else
    {
        removeLess(val, n->l);
        removeLess(val, n->r);
        remove(n->val, n);
    }
}

template<typename T>
bool rbtree<T>::search(T val) { return static_cast<bool>(search(val, root)); }

template<typename T>
typename rbtree<T>::node* rbtree<T>::search(T &val, rbtree::node *&n)
{
    if (n == nullptr) return n;
    if (n->val == val)
        return n;
    else if (val < n->val)
        search(val, n->l);
    else if (val > n->val)
        search(val, n->r);
}

template<typename T>
T rbtree<T>::max() { return max(root)->val; }

template<typename T>
typename rbtree<T>::node *rbtree<T>::max(node *mn)
{
    while (mn->r != nullptr)
        mn = mn->r;
    return mn;
}

template<typename T>
T rbtree<T>::min() { return min(root)->val; }

template<typename T>
typename rbtree<T>::node *rbtree<T>::min(node *mn)
{
    while (mn->l != nullptr)
        mn = mn->l;
    return mn;
}

template<typename T>
void rbtree<T>::print(std::ostream &ost) { print("", root, false, ost); }

template<typename T>
void rbtree<T>::print(const std::string& prefix, const node* n, bool isLeft, std::ostream &ost)
{
    if( n != nullptr )
    {
        ost << prefix;

        if (n==root)
            ost << "> ";
        else
            ost << (isLeft ? "├── " : "└── " );

        std::cout << (n->c == RED ? "(": "[") << n->val << (n->c == RED ? ")": "]") << std::endl;

        print( prefix + (isLeft ? "│   " : "    "), n->l, true, ost);
        print( prefix + (isLeft ? "│   " : "    "), n->r, false, ost);
    }
}

template<typename T>
void rbtree<T>::leftRotate(node *&n)
{
    node *nr = n->r;
    n->r = nr->l;

    if (n->r != nullptr)
        n->r->p = n;
    nr->p = n->p;

    if (n->p == nullptr)
        root = nr;
    else if (n == n->p->l)
        n->p->l = nr;
    else
        n->p->r = nr;

    nr->l = n;
    n->p = nr;
}

template<typename T>
void rbtree<T>::rightRotate(node *&n)
{
    auto nr = n->l;
    n->l = nr->r;

    if (n->l != nullptr)
        n->l->p = n;
    nr->p = n->p;

    if (n->p == nullptr)
        root = nr;
    else if (n == n->p->l)
        n->p->l = nr;
    else
        n->p->r = nr;

    nr->r = n;
    n->p = nr;
}

template class rbtree<int8_t>;
template class rbtree<int16_t>;
template class rbtree<int32_t>;
template class rbtree<int64_t>;
template class rbtree<uint8_t>;
template class rbtree<uint16_t>;
template class rbtree<uint32_t>;
template class rbtree<uint64_t>;
template class rbtree<double>;
template class rbtree<float>;
