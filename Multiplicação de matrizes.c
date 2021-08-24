/* 
 * Nome: Maria Carolina Resende Jaudacy  Matrícula: 667477
 * Tempo sequencial registrado para width = 2000
 *   1m28.538s (real)
 *   1m28.219s (user)
 *   0m0.109s (sys)
 * Tempo paralelo registrado para width = 2000
 *   0m35.362s (real)
 *   3m27.422s (user)
 *   0m15.438s (sys)
 */

#include <stdio.h>
#include <stdlib.h>

void mm(double* a, double* b, double* c, int width) 
{
 int i, j, k;
 #pragma omp parallel for private(i)
 for (i = 0; i < width; i++) {
    #pragma omp parallel for private(j)
    for (j = 0; j < width; j++) {
      double sum = 0;      
      #pragma omp parallel for private(k) reduction(+:sum)
      for (k = 0; k < width; k++) {
	    double x = a[i * width + k];
	    double y = b[k * width + j];
	    sum += x * y;
      }
      c[i * width + j] = sum;
    }
  }
}

int main()
{
  int i, j, width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));

  #pragma omp parallel for private(i)
  for(i = 0; i < width; i++) {
    #pragma omp parallel for private(j)
    for(j = 0; j < width; j++) {
      a[i*width+j] = i;
      b[i*width+j] = j;
      c[i*width+j] = 0;
    }
  }

  mm(a,b,c,width);

   //for(int i = 0; i < width; i++) {
    //for(int j = 0; j < width; j++) {
      //printf("\n c[%d][%d] = %f",i,j,c[i*width+j]);
    //}
   //}
}