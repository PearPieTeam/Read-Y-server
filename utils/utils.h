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

class DataBaseUtils {
public:
    static pqxx::connection establishConnection();
    static pqxx::work startWork(pqxx::connection c);
    static void closeConnection(pqxx::connection c);
};

class User {
public:
    string id;
    string avatar;
};


#endif //SERVERBACKEND_UTILS_H
