#include <iostream>
#include <random>
#include <ctime>

#include "list.h"
#include "array.h"

template <class T>
void print(T &arr)
{
    std::cout << "array:\n";
    if (arr.isEmpty()) std::cout << arr.typeName() << " is empty\n";
    for (uint64_t i=0; i < arr.size() and !arr.isEmpty(); i++)
    {
        std::cout << i <<". <" << arr[i] << ">\n";
    }
    std::cout << std::endl;
}

template<typename T>
void removeAX(T &arr, float &a) {
    auto ax = a * average3(arr);
    for (uint64_t i=0; i < arr.size(); i++)
    {
        if (arr[i] < ax)
        {
            arr.remove(i);
            i--;
        }
    }
}

template <class T>
double average3(T &arr)
{
    const int n = 3;
    int32_t max3[n];
    for (int i=0; i < n; i++)
    {
        max3[i] = std::numeric_limits<int32_t>::min();
        for (uint64_t j=0; j < arr.size(); j++)
        {
            if (i != 0)
            {
                if (arr[j] >= max3[i-1])
                {
                    continue;
                }
            }
            if (max3[i] < arr[j])
            {
                max3[i] = arr[j];
            }
        }
    }
    int64_t sum=0;
    for (int32_t &i : max3)
    {
         sum += i;
    }
    return static_cast<double>(sum/3.0);
}

void fill(array &arr, list &list, uint64_t size)
{
    //std::mt19937 generator(time(nullptr));
    std::mt19937 generator(0);
    std::uniform_int_distribution<int32_t> distribution( // (-2^31, 2^31 - 1)
            std::numeric_limits<int32_t>::min(),
            std::numeric_limits<int32_t>::max());
    for (uint i = 0; i < size; i++)
    {
        int64_t num = distribution(generator);
        arr[i] = num;
        list.push_back(num);
    }
}

int main()
{
    float a=0;
    std::cout << "A:= ";
    std::cin >> a;

    uint64_t size=0;
    std::cout << "Array and list size:= ";
    std::cin >> size;

    array array(size);
    list list;

    time_t ts, te;

    fill(array, list, size);

    time(&ts);
    removeAX(array, a);
    time(&te);
    std::cout << "\n";
    std::cout << "Size of array: " << array.size() << "\n";
    std::cout << "was deleted " << size - array.size() << " elements\n";
    std::cout << "computing time: " << te - ts << " seconds"<< "\n";

    time(&ts);
    removeAX(list, a);
    time(&te);
    std::cout << "-------\n";
    std::cout << "Size of double linked list: " << list.size() << "\n";
    std::cout << "was deleted " << size - list.size() << " elements\n";
    std::cout << "computing time: " << te - ts << " seconds" << std::endl;

    return 0;
}