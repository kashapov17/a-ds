#include <iostream>
#include <vector>
#include <random>

namespace instertionsort {
    template<typename T>
    std::vector<T> insertionsort(std::vector<T> v)
    {
        for (int j, i = 1; i < v.size(); i++)
        {
            int key = v[i];
            for (j = i; j > 0 && v[j - 1] > key; j--)
                v[j] = v[j - 1];
            v[j] = key;
        }
        return v;
    }
}

namespace shellsort {
    template <typename T>
    std::vector<T> shellsort(std::vector<T> v)
    {
        for (uint step = v.size()/2; step > 0; step/=2)
        {
            for (int j, i=step; i < v.size(); i++)
            {
                int key = v[i];
                for (j = int(i-step); j >= 0 && v[j] > key; j-=step)
                    v[j+step] = v[j];
                v[j+step] = key;
            }
        }
        return v;
    }
}

namespace selectionsort
{
    template<typename T>
    std::vector<T> selectionsort(std::vector<T> v)
    {
        for (uint i = 0; i < v.size(); i++)
        {
            uint m_idx = i;
            for (uint j = i + 1; j < v.size(); j++)
                if (v[j] < v[m_idx])
                    m_idx = j;
            std::swap(v[i], v[m_idx]);
        }
        return v;
    }
}

namespace quicksort
{
    template<typename T>
    uint qpart(std::vector<T> &v, uint &l, uint &r)
    {
        int p = v[l];
        uint i = l + 1;
        for (uint j = l + 1; j <= r; j++)
            if (v[j] < p)
                std::swap(v[j], v[i++]);
        std::swap(v[l], v[i - 1]);
        return i - 1;
    }

    template<typename T>
    uint chpivot(std::vector<T> &v, uint &l, uint &r)
    {
        std::mt19937 generator(time(nullptr));
        std::uniform_int_distribution<uint> distribution(l,r);
        return distribution(generator);
    }

    template<typename T>
    void qsort(std::vector<T> &v, uint l, uint r)
    {
        if (l >= r)
            return;
        uint i = chpivot(v,l,r);
        std::swap(v[l], v[i]);
        uint j = qpart(v, l, r);
        if (j != 0)
            qsort(v, l, j - 1);
        qsort(v, j + 1, r);
    }

    template<typename T>
    std::vector<T> qsort(std::vector<T> v)
    {
        qsort(v, 0, v.size()-1);
        return v;
    }
}


template <typename T>
void print(const std::vector<T> &v)
{
    std::cout << "\n\tsorted seq: [ ";
    for (const auto &it : v)
    {
        std::cout << "<" << it  << "> ";
    }
    std::cout << "]\n";
}

int main()
{
    std::vector<int> v {-1, 7, 3, 210, -10, 1, 1, 2, 3, 10, 20, 2, 5, 6, 1, 0, 8, 4};

    std::cout << "\n<<insertion sort>>";
    print(instertionsort::insertionsort(v));

    std::cout << "\n<<Shell sort>>";
    print(shellsort::shellsort(v));

    std::cout << "\n<<selection sort>>";
    print(selectionsort::selectionsort(v));

    std::cout << "\n<<quick sort>>";
    print(quicksort::qsort(v));

    return 0;
}