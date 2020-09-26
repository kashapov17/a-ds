//
// Created by yaroslav on 18.09.2020.
//

#include <cstdint>
#include <string>

#ifndef WORK2_ARRAY_H
#define WORK2_ARRAY_H

class array {
public:
    explicit array(uint64_t &size);
    ~array();
    void remove(uint64_t idx);
    const uint64_t size() const;
    int32_t& operator[](const uint64_t &idx);
    bool isEmpty();
    std::string typeName();

private:
    uint64_t _size;
    int32_t *first;
};


#endif //WORK2_ARRAY_H
