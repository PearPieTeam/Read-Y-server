//
// Created by xRoBoTx on 07.09.2019.
//

#ifndef SERVERBACKEND_UTILS_H
#define SERVERBACKEND_UTILS_H

#include <iostream>

using namespace std;

class Utils {

public:
   static void commandToFile(string command, string fileName);
};

class DataBaseUtils {
public:
    static void establishConnection();
};


#endif //SERVERBACKEND_UTILS_H
