mkdir libs
cd libs
git clone https://github.com/oktal/pistache.git
git submodule update --init
cd pistache
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
cd ../../..
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release 
make