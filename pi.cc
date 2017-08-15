#include <boost/mpi.hpp>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include "omp.h"

int main(int argc, char** argv) {
  boost::mpi::environment env(argc, argv);
  boost::mpi::communicator world;
  int id = world.rank();
  int n = world.size();
  const int N = 1000000000;

  const auto& init_time = std::chrono::high_resolution_clock::now();

  double local_sum = 0.0;

  double global_sum;

#ifdef NUM_THREADS
  omp_set_num_threads(NUM_THREADS);
#endif

#pragma omp parallel
  {
    if (id == 0 && omp_get_thread_num() == 0) {
      printf("Number of procs: %d\n", n);
      printf("Number of threads: %d\n", omp_get_num_threads());
    }
#pragma omp for reduction (+:local_sum) schedule(static, 1)
    for (int i = id; i < N; i += n) {
      if (i == 0) continue;
      double term = 4.0 / (2 * i - 1);
      for (int j = 0; j < 20; j++) term = sin(term);
      if ((i & 1) == 0) {
        term = -term;
      }
      local_sum += sin(term);
    }
  }

  boost::mpi::reduce(world, local_sum, global_sum, std::plus<double>(), 0);

  const auto& end_time = std::chrono::high_resolution_clock::now();

  if (id == 0) {
    printf("sum: %.10f\n", global_sum);
    printf(
        "Time: %f\n",
        std::chrono::duration_cast<std::chrono::duration<double>>(end_time - init_time).count());
  }
  // int pid =

  //     if (world.rank() == 0) {
  //   int minimum;
  //   reduce(world, my_number, minimum, mpi::minimum<int>(), 0);
  //   std::cout << "The minimum value is " << minimum << std::endl;
  // }
  // else {
  //   reduce(world, my_number, mpi::minimum<int>(), 0);
  // }

  return 0;
}
