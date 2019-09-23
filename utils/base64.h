//
// Created by xRoBoTx on 23.09.2019.
//

#ifndef SERVERBACKEND_BASE64_H
#define SERVERBACKEND_BASE64_H

#include <vector>
#include <string>

class Base64 {
public:
    static const std::string encode(const void* data, const size_t &len);
    static const std::string decode(const void* data, const size_t &len);
};


#endif //SERVERBACKEND_BASE64_H
