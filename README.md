# Optimised-Read-Until-API

TODO:

- Add code documentation
- Clean up CMakeLists.txt
- Remove unused client files and executables
- Remove cached files from directory
- Write up installation guide

```
export MY_INSTALL_DIR=$HOME/grpcinstall
mkdir -p $MY_INSTALL_DIR
export PATH="$MY_INSTALL_DIR/bin:$PATH"

wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.19.6/cmake-3.19.6-Linux-x86_64.sh
sh cmake-linux.sh -- --skip-license --prefix=$MY_INSTALL_DIR
rm cmake-linux.sh

cd ~
git clone --recurse-submodules -b v1.42.0 https://github.com/grpc/grpc
cd grpc/
mkdir -p cmake/build && cd cmake/build


cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
	  
make -j
make install
	  
cd ~
git clone git@github.com:brianzhang2101/Optimised-Read-Until-API.git
mv Optimised-Read-Until-API/minknow_api/ ~/grpc/examples/cpp/
mv Optimised-Read-Until-API/proto/ ~/grpc/examples/

cd ~/grpc/examples/cpp/minknow_api/cmake/build  
cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
make -j

```
