all: driver

driver: driver.cpp
	g++ -std=c++11 -Wall driver.cpp -o driver
