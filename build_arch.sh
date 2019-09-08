#Init submodules
git submodule update --init --recursive

#Build project
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
