#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>

// Creates an array of numbers. Each number has a value from 0 - 7 (corresponds with the processor's number)
float *create_nums(int num_elements) {
  float *nums = (float *)malloc(sizeof(float) * num_elements);
  assert(nums != NULL);
  int i;
  for (i = 0; i < num_elements; i++) {
    nums[i] = i;
  }
  return nums;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: avg num_elements_per_proc\n");
    exit(1);
  }

  int num_elements_per_proc = atoi(argv[1]);

  MPI_Init(NULL, NULL);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Create an array of elements on all processes.
  float *nums = NULL;
  nums = create_nums(num_elements_per_proc);

  // Sum the numbers locally
  float local_sum = 0;
  int i;
  for (i = 0; i < num_elements_per_proc; i++) {
    local_sum += nums[i];
  }

  // Reduce all of the local sums into the global sum
  float global_sum;
  MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
             MPI_COMM_WORLD);

  // Print the result
  if (world_rank == 0) {
    printf("Reduction result from Rank 0: %d\n", global_sum);
  }

  // Clean up
  free(nums);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
}