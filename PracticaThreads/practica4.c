#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int *arreglo3;
int j = 0;

void* suma(void *parametro)
{
    int *a = (int*)parametro;
    printf("%d + %d = %d\n", a[0], a[1], a[0] + a[1]);
    arreglo3[j] = a[0] + a[1];
    j++;
    pthread_exit(0);
}

int main(int argc, char *argv[])
{

    int *arreglo1 = malloc (sizeof(int)*100);
    int *arreglo2 = malloc (sizeof(int)*100);
    arreglo3 = malloc (sizeof(int) *100);
    pthread_t *ptr = malloc (sizeof(pthread_t)*100);
    int *tmp = malloc (sizeof(int)*2);

    for(int i = 0; i < 100; i++)
    {
      arreglo1[i] = i;
      arreglo2[i] = i;
      tmp[0] = arreglo1[i];
      tmp[1] = arreglo2[i];
      pthread_create(&ptr[i], NULL, suma, (void*)tmp);
      pthread_join(ptr[i], NULL);
    }
    return 0;
}
