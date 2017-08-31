/*
 * Jose Manuel Beauregard A01021716
 * Francisco Huelsz A01019512
 *
 * Actividad 5
 * línea de compilacion:
 * gcc -o (nombre del ejecutable) Act5.c -lpthread
 * ./(nombre del ejecutable) (numero n) (numero k) 
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//generara el comando que buscara los comandos ejecutados por el root de la computadora
void* command()
{
    printf("Getting the commands running by root: \n");	
    //crea un archivo donde guardara el output de dicho comando
    FILE* f = popen("ps -fea | grep root | grep -v grep | grep -v avahi","r");
    char lines[200];
    //se lee el linea por linea y las imprime en pantalla 
    do {
    fprintf(stdout, "%s\n", lines);
    } while(fgets(lines, 200, f));
    //cerramos el archivo y salimos del proceso hijo
    pclose(f);
    pthread_exit(0);
}

void* mPepe()
{
    printf("Matricula:\n");
    //A
    printf("\n  A  \n A A \nA   A\nAAAAA\nA   A\n");
    //0
    printf("\n 000 \n0   0\n0   0\n0   0\n 000 \n");
    //1
    printf("\n111  \n  1  \n  1  \n  1  \n11111\n");
    //0
    printf("\n 000 \n0   0\n0   0\n0   0\n 000 \n");
    //2
    printf("\n2222 \n    2\n22222\n2    \n22222\n");
    //1
    printf("\n111  \n  1  \n  1  \n  1  \n11111\n");
    //7
    printf("\n77777\n   7 \n  7  \n 7   \n7    \n");
    //1
    printf("\n111  \n  1  \n  1  \n  1  \n11111\n");
    //6
    printf("66666\n6     \n6 666\n66  6\n66666\n" );
}

void* pepe()
{
    printf("Nombre:\n");
    //J
    printf("JJJJJJ\n  J  \n  J   \nJ J  \nJJJ  \n" );
    //O
    printf("\n OOO \nO   O\nO   O\nO   O\n OOO \n");
    //S
    printf("\nSSSSS\nS    \nSSSSS\n    S\nSSSSS\n");
    //E
    printf("\nEEEEE\nE    \nEEE  \nE    \nEEEEE\n");
    printf("---------------------------------------\n");
    mPepe();
}

void* mPaco()
{
    printf("Matricula:\n");
    //A
    printf("\n  A  \n A A \nA   A\nAAAAA\nA   A\n");
    //0
    printf("\n 000 \n0   0\n0   0\n0   0\n 000 \n");
    //1
    printf("\n111  \n  1  \n  1  \n  1  \n11111\n");
    //0
    printf("\n 000 \n0   0\n0   0\n0   0\n 000 \n");
    //1
    printf("\n111  \n  1  \n  1  \n  1  \n11111\n");
    //9
    printf("\n99999\n9   9\n99999\n    9\n99999\n");
    //5
    printf("\n55555\n5    \n55555\n    5\n55555\n");
    //1
    printf("\n111  \n  1  \n  1  \n  1  \n11111\n");
    //2
    printf("\n2222 \n    2\n22222\n2    \n22222\n");

}

void* paco()
{
    printf("Nombre:\n");
    //P
    printf("PPPPP\nP   P\nPPPPP\nP    \nP    \n" );
    //A
    printf("\n  A  \n A A \nA   A\nAAAAA\nA   A\n");
    //C
    printf("\nCCCCC\nC    \nC    \nC    \nCCCCC\n");
    //O
    printf("\n OOO \nO   O\nO   O\nO   O\n OOO \n");
    printf("---------------------------------------\n");
    mPaco();
}

//esta funcion imprimira los nombres del equipo 
void* drawNames()
{
    pepe();
    printf("\n\n");
    paco();
    pthread_exit(0);
}


void * factorialth(void * inpt){
    //regresa n! siempre y cuando n >= 0

    //Obtener el valor de la entrada
    int n = *((int *) inpt);

    //Verificar entrada valida
    if (n < 0)
        return (void *) 0;

    unsigned long out = 1;
    int i;

    //Factorial iterativo
    for(i = 1; i <= n; i++){
        out *= i;
    }
    //printf("%d! = %d\n", n, out);
    return (void *) out;
}

unsigned long combinaciones (int n, int r){

    pthread_t tid_f1, tid_f2, tid_f3;
    pthread_attr_t attr_f1, attr_f2, attr_f3;

    int dif = n-r;

    //Verificar entrada valida
    if ( dif < 0 ) {
        printf("Error: entrada no valida!\n");
        exit(-1);
    }

    //Lanzar thread para calcular los factoriales

    //Thread de factorial(n)
    pthread_attr_init(&attr_f1);
    pthread_create(&tid_f1, &attr_f1, factorialth, &n);

    //Thread de factorial(r)
    pthread_attr_init(&attr_f2);
    pthread_create(&tid_f2, &attr_f2, factorialth, &r);

    //Thread de factorial(n-r)
    pthread_attr_init(&attr_f3);
    pthread_create(&tid_f3, &attr_f3, factorialth, &dif);


    //Variable temporal para recibir los datos
    void * temp = NULL;

    //Variables para guardar los factoriales calculados
    unsigned long fn, fr, fdif;

    //Join del thread factorial(n)
    pthread_join(tid_f1, &temp);
    fn = (unsigned long)temp;

    //Join del thread factorial(r)
    pthread_join(tid_f2, &temp);
    fr = (unsigned long)temp;

    //Join del thread factorial(n-r)
    pthread_join(tid_f3, &temp);
    fdif = (unsigned long)temp;

    //Calculo final n!/ ( r! * (n - r)! )
    return fn / ( fr * fdif);
}

int main(int argc, char* argv[])
{
    pthread_t tid_1, tid_2, tid_f1, tid_f2, tid_f3;
    pthread_attr_t attr_1, attr_2, attr_f1, attr_f2, attr_f3;

    //Primer thread: nombres y matrículas
    pthread_attr_init(&attr_1);
    pthread_create(&tid_1, &attr_1, drawNames, NULL);
    pthread_join(tid_1, NULL);

    printf("-----------------------------------\n");

    //Segundo thread: procesos
    pthread_attr_init(&attr_2);
    pthread_create(&tid_2, &attr_2, command, NULL);
    pthread_join(tid_2, NULL);

    printf("-----------------------------------\n");


    //Verificar numero de argumentos
    if(argc != 3) {
        printf("Error en numero de argumentos (%d)\n", argc);
        exit(-1);
    }

    //Parsear la entrada
    int n = atoi(argv[1]);
    int r = atoi(argv[2]);

    //Calcular combinaciones
    unsigned long res = combinaciones(n, r);

    //Imprimir resultado
    printf("Combinaciones:\nnCr( %d, %d) = %lu\n", n, r, res);

}
