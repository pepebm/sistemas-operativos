#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* funcion(void* parametros)
{
   int *a = (int *)parametros;
   printf("%d elevado a %d=%f\n", a[0], a[1], pow((double)a[0], (double)a[1]));
   pthread_exit(0);
}

int main(int argc, char *argv[])
{
   int i = 0;
   pthread_t *ptr;
   srand(time(0));
   int *arreglo;

   arreglo = malloc (sizeof(int*3);
   ptr = malloc(sizeof(pthread_t)*5);

   for(i = 0; i < 5; i++)
   {
      arreglo[0] = rand()%12+1;
      arreglo[1] = rand()%6+1;
      pthread_create(&ptr[i], NULL, funcion, (void*)arreglo);
      pthread_join(ptr[i], NULL);
   }

   return 0;
}
