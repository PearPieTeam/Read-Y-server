//
// Created by xRoBoTx on 07.09.2019.
//

#ifndef SERVERBACKEND_UTILS_H
#define SERVERBACKEND_UTILS_H

#include <iostream>
#include <pqxx/pqxx>

using namespace std;

class Utils {

public:
    static void commandToFile(string command, string fileName);
};

class User {
public:
    string id;
    string avatar;
};


#endif //SERVERBACKEND_UTILS_H
