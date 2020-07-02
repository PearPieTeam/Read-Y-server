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
