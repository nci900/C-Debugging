#include <stddef.h>   // size_t
#include <stdlib.h>   // malloc()
#include <stdio.h>    // FILE, stderr, fprintf()
#include <math.h>     // M_PI, sin()

void derivative(double* dydx, const double* x, const double* y, const size_t N);
void write_csv(const char* fname, const double* x, const double* y, const double* dydx, const size_t N);

int main(int argc, char* argv[]) {
  // We want an input argument for the name of the output file
  if (argc != 2) {
    // Print to standard error
    fprintf(stderr, "ERROR: %s requires one input argument for the output .csv file!\n", argv[0]);
    return 1;
  }

  // Populate x and y arrays
  // CHALLENGE: Once you get this code working, try taking N and dx
  //            as command line arguments.
  //            The sscanf function will be useful for that.
  size_t N = 1800;  // Number of points
  double dx = 0.1;  // Step between x values
  double* x = malloc(sizeof(*x) * N);
  double* y = malloc(sizeof(*y) * N);
  double *dydx = malloc(sizeof(*dydx) * N);

  for (size_t i = 0; i < N; ++i) {
    x[i] = i*dx * M_PI / 180.; // M_PI is the pi constant, defined in math.h
    y[i] = sin(x[i]); // NOTE: sin() for double precision,
                      //       sinf() for float (single precision),
                      //       and sinl() for long
  }

  // Calculate the derivative
  derivative(dydx, x, y, N);

  // Write the result to file
  write_csv(argv[1], x, y, dydx, N);
}


// Calculate the derivative of y(x), where x and y are both of length N
// dydx is output array. If it was a return value, we would have to allocate
// it in this function, which could be inefficient if the caller wanted to
// re-use an existing memory allocation.
void derivative(double* dydx, const double* x, const double* y, const size_t N) {
  for (size_t i = 0; i < N; ++i) {
    // Apply finite difference stencil
    dydx[i] = y[i+1] - y[i-1] / x[i+1] - x[i-1];
  }
}

void write_csv(
  const char* fname,
  const double* x,
  const double* y,
  const double* dydx,
  const size_t N
) {
  FILE* fid = fopen(fname, "w");  // Open the file `fname` in write mode
                                  // `fid` is a file handle used to work with an open file

  // Write the header row
  fprintf(fid, "x,y,dydx\n");

  // Write the data rows
  for (size_t i = 0; i < N; ++i) {
    fprintf(fid, "%g,%g,%g\n", x[i], y[i], dydx[i]);
  }

  // Close the file
  fclose(fid);
}
