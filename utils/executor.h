//
// Created by xRoBoTx on 23.09.2019.
//

#ifndef THIRDWEEKTASK_EXECUTOR_H
#define THIRDWEEKTASK_EXECUTOR_H

#include <fstream>

int executeCode(const std::string& code)
{
    const std::string dynamic_filename("dynamic.cpp");
#if __WIN32
    const std::string dynamic_executable("dynamic.out");
#endif

#if __unix__
    const std::string dynamic_executable("./dynamic.out");
#endif
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
            << "std::cout<<\"Result: \"<<i<<std::endl;                 \n"
            << "return EXIT_SUCCESS;                                   \n"
            << "}                                                      \n";
    dynamic.close();

#if __WIN32
    const std::string build_command(".\\Compiler\\bin\\g++ -static -fpermissive -O2 -pedantic -w " + dynamic_filename + " -o " + dynamic_executable);
#endif

#if __unix__
    const std::string build_command("g++ -static -fpermissive -O2 -pedantic -w " + dynamic_filename + " -o " + dynamic_executable);
#endif
    //const std::string build_command("g++ -std=c++14 -static -O2 -pedantic -w " + dynamic_filename + " -o " + dynamic_executable);
    bool it_didnt_compile = system(build_command.c_str());
    if(it_didnt_compile)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return system(dynamic_executable.c_str());
    }
}

#endif //THIRDWEEKTASK_EXECUTOR_H
