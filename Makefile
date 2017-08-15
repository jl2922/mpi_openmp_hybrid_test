
.PHONY: all

all: pi.cc
	mpic++ -std=c++11 -Wall -Wextra -O3 -fopenmp pi.cc -o pi -lboost_mpi -lboost_serialization