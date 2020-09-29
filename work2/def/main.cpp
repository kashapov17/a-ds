#include <iostream>
#include <queue>
#include <limits>
#include <random>
#include <chrono>

double averageMax3(std::queue<int32_t> &q)
{
    const int n = 3;
    int32_t max3[n];
    for (int i=0; i < n; i++)
    {
        auto b = q;
        max3[i] = std::numeric_limits<int32_t>::min();
        for (uint64_t j=0; !b.empty(); j++)
        {
            auto elem = b.front();
            b.pop();
            if (i != 0)
            {
                if (elem >= max3[i-1])
                {
                    continue;
                }
            }
            if (max3[i] < elem)
            {
                max3[i] = elem;
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

void removeLessAX(std::queue<int32_t> &q, float &a) {
    auto ax = a * averageMax3(q);
    std::cout << ax << "\n";
    std::queue<int32_t> b;
    for (uint64_t i=0; !q.empty(); i++)
    {
        if (q.front() >= ax)
        {
            b.push(q.front());
        }
        q.pop();
    }
    b.swap(q);
}

void fill(std::queue<int32_t> &q, uint64_t size)
{
    std::mt19937 generator(time(nullptr));
    std::uniform_int_distribution<int32_t> distribution( // [-2^31, 2^31 - 1]
            std::numeric_limits<int32_t>::min(),
            std::numeric_limits<int32_t>::max());
    for (uint64_t i = 0; i < size; i++)
    {
        int32_t num = distribution(generator);
        q.push(num);
    }
}

int main() {

    float a=0;
    std::cout << "A = ";
    std::cin >> a;

    uint64_t size=0;
    std::cout << "Array and list size:= ";
    std::cin >> size;

    std::queue<int32_t> q;
    fill(q, size);

    auto time_start = std::chrono::high_resolution_clock::now();
    removeLessAX(q, a);
    auto time_end = std::chrono::high_resolution_clock::now();
    std::cout << "\n";
    std::cout << "Size of array: " << q.size() << "\n";
    std::cout << size - q.size() << " elements " << "was deleted\n" ;
    std::cout << "computing time: " << std::chrono::duration_cast<
            std::chrono::milliseconds>(time_end - time_start).count() << " milliseconds"<< "\n";
    return 0;
}
