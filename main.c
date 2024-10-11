#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(const char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
} 

double f(const double x, const double y){
  return (sin(x * x + y * y));
}

double Trapezoidal_Rule(const double a, const double b, const double c, const double d, const int nx, const int ny, int threads){
  double hx, hy, integral = 0, xi, yj;
  
  hx = (b - a) / nx;
  hy = (d - c) / ny;

  #pragma omp parallel for num_threads(threads) reduction(+: integral) schedule(dynamic)
  for(int i = 0; i < nx; i++){
    for(int j = 0; j < ny; j++){
      xi = a + hx / 2 + i * hx;
      yj = a + hy / 2 + j * hy;
      integral += hx * hy * f(xi, yj); 
    }
  }
  return integral;
}

int main(int argc, char* argv[]){
  double result = 0;
  double itime, ftime, exec_time;
  

  if (argc != 4) {
    printf("Uso: %s num1 num2 num3\n", argv[0]);
    return 1;
  }
  
  int threads = atoi(argv[1]);
  int intervals_x = atoi(argv[2]);
  int intervals_y = atoi(argv[3]);
  
  itime = omp_get_wtime();
  result = Trapezoidal_Rule(0.0, 1.5, 0.0, 1.5, intervals_x, intervals_y, threads);
  ftime = omp_get_wtime();
  exec_time = ftime - itime;
  printf("%d, %d, %d, %15.15f\n", threads, intervals_x, intervals_y, exec_time);
}