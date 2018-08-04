echo Compiling with main1.cpp as main...
g++ -std=c++11 -o main1 src/main1.cpp src/*/*.cpp src/*/*/*.cpp

echo Compiling with main2.cpp as main...
g++ -std=c++11 -o main2 src/main2.cpp src/*/*.cpp src/*/*/*.cpp

echo Done.
