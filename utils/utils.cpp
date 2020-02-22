//
// Created by xRoBoTx on 07.09.2019.
//

#include "utils.h"
#include <iostream>
#include <fstream>
#include <cstring>

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

/*connection DataBaseUtils::establishConnection() {
    try {
        connection c("dbname = Chat user = Admin password = 228995 host = 127.0.0.1 port = 5432");
        if (c.is_open()) {
            cout << "Opened database successfully: " << c.dbname() << endl;
            return c;
        } else {
            cout << "Can't open database" << endl;
        }
        //c.disconnect ();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}

void DataBaseUtils::closeConnection(connection c) {
    c.close();
}

pqxx::work DataBaseUtils::startWork(pqxx::connection c) {
    return pqxx::work(c);
}*/
