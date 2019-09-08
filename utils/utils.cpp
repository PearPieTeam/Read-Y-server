//
// Created by xRoBoTx on 07.09.2019.
//

#include "utils.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

void Utils::commandToFile(string command, string fileName) {
    string s(command + " > " + fileName);
    char cstr[s.size() + 1];

    strcpy(cstr, s.c_str());
    std::cout << system(cstr) << std::endl;
    ifstream neofetchFile;
    neofetchFile.open(fileName);
    while (!neofetchFile.eof())
        getline(neofetchFile, fileName);
    neofetchFile.close();
}

void DataBaseUtils::establishConnection() {
    try {
        connection C("dbname = testdb user = postgres password = cohondob \
      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
        }
        //C.disconnect ();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}
