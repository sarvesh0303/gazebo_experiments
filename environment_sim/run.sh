mkdir build
cd build
cmake ../
make
cd ../
export GAZEBO_PLUGIN_PATH=./build
gzserver -u --verbose blank.world