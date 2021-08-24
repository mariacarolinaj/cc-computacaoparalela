/*
 * Algoritmo original do Crivo de Eratóstenes sequencial: https://ideone.com/JU5CfV
 *
 * Tempo sequencial registrado para n = 100000000: 
 *   1.423s (real)
 *   1.250s (user)
 *   0.109s (sys)
 * Tempo paralelo registrado com o uso de 4 threads para n = 100000000:
 *   1.324s (real)
 *   2.672s (user)
 *   0.031s (sys)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int sieveOfEratosthenes(int n)
{
   omp_set_num_threads(4);

   // Create a boolean array "prime[0..n]" and initialize all entries it as true. 
   // A value in prime[i] will finally be false if i is Not a prime, else true.
   int primes = 0; 
   bool *prime = (bool*) malloc((n+1)*sizeof(bool));
   int sqrt_n = sqrt(n);
   
   memset(prime, true,(n+1)*sizeof(bool));
   int p;
   #pragma omp parallel for private(p)
   for (p=2; p <= sqrt_n; p++)
   {
       // If prime[p] is not changed, then it is a prime
       if (prime[p] == true)
       {
	   int i;
           // Update all multiples of p
   	   #pragma omp parallel for private (i)
           for (i=p*2; i<=n; i += p)
           prime[i] = false;
        }
    }

    // count prime numbers
    #pragma omp parallel for private(p) reduction(+:primes)
    for (p=2; p<=n; p++)
       if (prime[p])
         primes++;

    return(primes);
}

int main()
{
   int n = 100000000;
   printf("%d\n",sieveOfEratosthenes(n));
   return 0;
} 