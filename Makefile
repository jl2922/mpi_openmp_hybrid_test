
.PHONY: all

all: pi.cc
	mpic++ -std=c++11 -Wall -Wextra -O3 -fopenmp -I /home/junhao/boost-1.63.0/include pi.cc -o pi -L /home/junhao/boost-1.63.0/lib -lboost_mpi -lboost_serialization