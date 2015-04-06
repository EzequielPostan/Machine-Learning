#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Cantidad de desvíos estandar de la media que determinan
// el dominio de la normal
#define DESV 5

/*
  normal: Función de la distribución normal
  x: valor a evaluar
  mu: media de la normal
  sigma: desvío estandar de la normal
  La ley está dada por
                      2
          1  /x - mu \
       - --- |-------|
          2   \sigma/
     e
    ---------------- 
    sqrt(2*pi)*sigma
*/
double normal(double x,double mu,double sigma)
{
  return exp(-pow((x-mu)/sigma,2.0)/2.0)/(sqrt(2*M_PI)*sigma);
}

// Prototipo de imprimirVectores, definida al final del archivo
void imprimirVectores(int n, int dim, double mu, double sigma, FILE *output,int clase);


/*
  EJERCICIO A:
  a) Los datos tienen d inputs, todos valores reales, correspondientes a la 
     posición del punto en un espacio d-dimensional. El output es binario, y 
     corresponde a la clase a la que pertenece el ejemplo. La clase 1 
     corresponde a puntos generados al azar, provenientes de una distribución 
     normal, con centro en el ( 1, 0, 0, .... , 0 ) y matriz de covarianza 
     diagonal, con desviación estándar igual a C. La clase 0 tiene 
     la misma distribución, pero centrada en el ( -1, 0, 0, .... , 0 ). 
     Los parámetros que se deben ingresar son d y n (enteros) y C (real). 
     De los n puntos generados, n/2 deben pertenecer a cada clase.

  ENTRADA DEL PROGRAMA
  n: tamaño del conjunto de datos generado
  d: dimensión del espacio del vector
  C: número real que determina el desvío estandar (sigma)
     con la relación sigma = C*sqrt(d)

  FORMA DE COMPILACIÓN Y EJECUCIÓN:
  $ gcc -Wall ejercicioB.c -o ejercicioB -lm
  $ ./ejercicioB n d C
  Ejemplo:
  $ ./ejercicioB 100 2 2.1
   genera un conjunto de 100 datos de dimensión 2 donde la mitad corresponde a
   valores de la clase 0 y los otros 50 a la clase 1 con un valor de C igual a
   2.1
*/

int main(int argc, char **argv)
{
  int n,d;
  double C,sigma;
  int i;
  FILE *fd;
  if(argc != 4)
    printf("\nNúmero de argumentos incorrecto\n\n"
           "ENTRADA DEL PROGRAMA\n"
           "  n: tamaño del conjunto de datos generado\n"
           "  d: dimensión del espacio del vector\n"
           "  C: número real que determina el desvío estandar (sigma)\n"
           "     con la relación sigma = C*sqrt(d)\n\n"

           "FORMA DE COMPILACIÓN Y EJECUCIÓN:\n"
           "  $ gcc -Wall ejercicioB.c -o ejercicioB -lm\n"
           "  $ ./ejercicioB n d C\n\n"
           "Ejemplo:\n"
           "  $ ./ejercicioB 100 2 2.1\n\n"
           "  genera un conjunto de 100 datos de dimensión 2 donde la mitad corresponde a\n"
           "  valores de la clase 0 y los otros 50 a la clase 1 con un valor de C igual a\n"
   "  2.1\n"
          ),exit(-1);

  //Obtenemos la entrada
  n = atoi(argv[1]);
  d = atoi(argv[2]);
  C = atof(argv[3]);

  //calculamos el desvío estandar
  sigma = C;

  //Creamos y completamos el archivo ejercicioA.names
  fd = fopen("ejercicioB.names","w");
  fprintf(fd,"0,1.\n");
  for(i = 0 ; i < d ; i++)
    fprintf(fd,"x%d: continuous.\n",i+1);

  // Cerramos el archivo
  fclose(fd);
 
  // Creamos el archivo ejercicioA.data
  fd = fopen("ejercicioB.data","w");

  // Lo completamos
  // Primero la n/2 vectores de la clase 1
  imprimirVectores(n/2,d,1,sigma,fd,1);
  // Luego n/2 vectores de la clase 0
  imprimirVectores(n/2,d,-1,sigma,fd,0);

  // Y cerramos el archivo
  fclose(fd);

  return 0;
}

/*
  imprimirVectores: Genera n vectores de dimensión dim seleccionados al azar
  de una distribución normal con centro en (mu,mu,...,mu) y desvío estandar
  sigma. Imprime los vectores usando el formato c4.5 en el archivo output
  n: número de vectores a generar
  dim: dimensión de los vectores
  mu: valor que determina el centro de la distribución
  sigma: desvío estandar de la distribución
  output: archivo donde se imprimen los valores
*/
void imprimirVectores(int n, int dim, double mu, double sigma, FILE *output,int clase)
{
  int i = dim;
  // El inicio del intervalo está en mu-5*sigma 
  // (nuestra constante DESV es igual a 5)
  double inicio2 = - DESV*sigma;
  double inicio = mu + inicio2;
  // La altura máxima de la normal se alcanza en la media mu, 
  // y la altura de la curva es 1/(sqrt(2*M_PI)*sigma);
  double altura = 1/(sqrt(2*M_PI)*sigma);

  // Tomamos dos puntos al azar y usamos un método de rechazo
  // para quedarnos con valores de x que simulen ser tomados de
  // una distribución normal
  double x,y;

  // seteamos la semilla de drand48()
  srand48(time(NULL));
  //printf("%f\n",drand48());

  while(n){
    x = inicio + 2*DESV*sigma*drand48();
    y = drand48()*altura;
    while(y > normal(x,mu,sigma)){
      x = inicio + 2*DESV*sigma*drand48();
      y = drand48()*altura;
    }
    fprintf(output,"%f,",x);
    i--;
    while(i){
      // Tomamos un punto en el rectángulo determinado por los extremos
      // (inicio,0) y (inicio+2*DESV*sigma,altura)
      x = inicio2 + 2*DESV*sigma*drand48();
      y = drand48()*altura;
      if(y <= normal(x,0,sigma)){
        fprintf(output,"%f,",x);
        i--;
      }
    }
    // imprimimos la clase
    fprintf(output,"%d\n",clase);

    // seteamos a i para dar dim iteraciones del bucle para
    // generar el siguiente vector
    i = dim;
    // Descontamos un vector a generar
    n--;
  }
  return;
}
