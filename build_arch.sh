mkdir libs
cd libs
#Clone pistache library
git clone https://github.com/oktal/pistache.git
cd pistache
git submodule update --init
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install

cd ../..

#Clone libpqcxx library
git clone https://github.com/jtv/libpqxx.git
cd libpqcxx
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

#Build project
cd ../..
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make