#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Handle input arguments to sum_array
typedef struct {
  double* arr;
  size_t len;
  double out;
} InputArgs;

// Sum up a segment of an array
// Has signature void* sum_array(void*) to work with pthreads
void* sum_array(void* args) {
  InputArgs* parsed_args = args;
  double sum = 0.;
  for (size_t i = 0; i < parsed_args->len; ++i)
    sum += parsed_args->arr[i];
  parsed_args->out = sum;
  return NULL;
}

int main(void) {
  const int nthreads = 4;       // Number of parallel threads
  pthread_t threads[nthreads];  // Stored thread handles
  InputArgs args[nthreads];     // Input arguments to each thread

  // Set up test array
  const size_t N = 1000;
  double* arr = malloc(sizeof(*arr) * N);
  for (size_t i = 0; i < N; ++i) {
    arr[i] = 1.0;
  }

  // Spawn threads which each sum a section of the array
  for (int i = 0; i < nthreads; ++i) {
    /* Set up input arguments for thread i */
    // Point to the start of the segment this thread should work on
    args[i].arr = &arr[i*N/nthreads];
    // Length of each array segment is N/nthreads
    // (assuming N is a multiple of nthreads)
    args[i].len = N/nthreads;

    // Spawn the thread and store its handle in threads[i]
    int status = pthread_create(&threads[i], NULL, sum_array, &args[i]);

    // non-zero status means a thread didn't launch properly
    assert(status == 0);
  }

  // Calculate the final sum
  double sum = 0.;
  for (int i = 0; i < nthreads; ++i) {
    // Join thread i to make sure it's finished executing
    pthread_join(threads[i], NULL);

    // Add its local sum to the total
    sum += args[i].out;
  }

  // Display the result
  printf("sum: %g\n", sum);
  return 0;
}
