//
// Created by xRoBoTx on 23.09.2019.
//

#ifndef THIRDWEEKTASK_EXECUTOR_H
#define THIRDWEEKTASK_EXECUTOR_H

#include <fstream>

int executeCode(const std::string& code, const std::string& outFile)
{
    const std::string dynamic_filename("./files/dynamic.cpp");
    const std::string dynamic_executable("./files/dynamic.out >" + outFile);

    std::ofstream dynamic(dynamic_filename);
    dynamic << "#include <iostream>                                    \n"
            << "#include <cstdlib>                                     \n"
            << "#include \"custom_math.h\"                             \n"
            << "CustomNumber n(double num) {                           \n"
            << "    CustomNumber _n(num);                              \n"
            << "    return _n;                                         \n"
            << "}                                                      \n"
            << "int main(){                                            \n"
            << "double i = static_cast<double>("<< code <<");          \n"
            << "std::cout<<i<<std::endl;                               \n"
            << "return EXIT_SUCCESS;                                   \n"
            << "}                                                      \n";
    dynamic.close();

    const std::string build_command("g++ -static -fpermissive -O2 -pedantic -w " + dynamic_filename + " -o " + dynamic_executable);

        if(system(build_command.c_str()))
    {
        return EXIT_FAILURE;
    }
    else
    {
        return system(dynamic_executable.c_str());
    }
}

#endif //THIRDWEEKTASK_EXECUTOR_H
