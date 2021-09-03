/* 
 * Tempo sequencial registrado: 
 *   6.172s (real) 6.168s (user) 0.000s (sys)
 * Tempo paralelo registrado com o uso de 2 threads e política de escalonamento estática:
 *   1.054s (real) 6.031s (user) 0.188s (sys)
 * Tempo paralelo registrado com o uso de 2 threads e política de escalonamento dinâmica:
 *   1.201s (real) 6.734s (user) 0.219s (sys)
 * Tempo paralelo registrado com o uso de 2 threads sem nenhuma política de escalonamento:
 *   1.245s (real) 6.859s (user) 0.188s (sys)
 */

#include <stdio.h>
#include <stdlib.h>

int main() 
{
   #pragma omp_set_num_threads(2)

   int i, j, n = 30000; 

   // Allocate input, output and position arrays
   int *in = (int*) calloc(n, sizeof(int));
   int *pos = (int*) calloc(n, sizeof(int));   
   int *out = (int*) calloc(n, sizeof(int));   

   // Initialize input array in the reverse order
   #pragma omp parallel for
   for(i=0; i < n; i++)
      in[i] = n-i;  

   // Print input array
   //  for(i=0; i < n; i++) 
   //    printf("%d ",in[i]);
    
   // Silly sort (you have to make this code parallel)
   #pragma omp parallel for shared (pos)
   for(i=0; i < n; i++) 
      #pragma omp parallel for reduction(+:pos[i]) schedule (static,100)
      for(j=0; j < n; j++)
           if(in[i] > in[j])
               pos[i]++;	

   // Move elements to final position
   for(i=0; i < n; i++) 
      out[pos[i]] = in[i];
   
   printf("%s ", "ordenado:");

   // print output array
   // for(i=0; i < n; i++) 
   //    printf("%d ",out[i]);

   // Check if answer is correct
   for(i=0; i < n; i++)
      if(i+1 != out[i]) 
      {
         printf("test failed\n");
         exit(0);
      }

   printf("test passed\n"); 
}  
