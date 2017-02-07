mkdir build
cd build
cmake ../
make
cd ../
mkdir dark
cd dark
cmake ../lights/
make
cd ../
export GAZEBO_PLUGIN_PATH=./build;export GAZEBO_PLUGIN_PATH="$GAZEBO_PLUGIN_PATH:./dark"
gzserver -u --verbose car3.world