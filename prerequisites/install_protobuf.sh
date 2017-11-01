sudo apt-get install autoconf automake libtool curl make g++ unzip git
git clone https://github.com/google/protobuf.git

cd protobuf # lets roll
./autogen.sh 
./configure
make -j8
make check
sudo make install
sudo ldconfig
pkg-config --cflags protobuf         # print compiler flags
pkg-config --libs protobuf           # print linker flags
pkg-config --cflags --libs protobuf  # print both

cd ..
