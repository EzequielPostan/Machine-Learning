#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>

void imprimirPuntos(int n,FILE *output);


/*
  EJERCICIO C:
  c) Espirales anidadas: Los datos tienen 2 inputs, x e y, que corresponden a 
     puntos generados al azar con una distribución UNIFORME (en dicho sistema 
     de referencia x-y)  dentro de un circulo de radio 1. El output es binario,
     correspondiendo la clase 0 a los puntos que se encuentran entre las curvas 
     ro = theta/4pi y ro = (theta + pi)/4pi (en polares) y la clase 1 al resto.
     De los n puntos generados, n/2 deben pertenecer a cada clase. La siguiente 
     figura es un ejemplo:
      https://sites.google.com/site/aprendizajeautomatizadounr/Inicio/practicos/tp0/espirales.jpg?attredirects=0

  ENTRADA DEL PROGRAMA
  n: tamaño del conjunto de datos generado

  FORMA DE COMPILACIÓN Y EJECUCIÓN:
  $ gcc -Wall ejercicioC.c -o ejercicioC -lm
  $ ./ejercicioC n
  Ejemplo:
  $ ./ejercicioC 100
  
  genera un conjunto de 100 datos donde la mitad corresponde a valores de la 
  clase 0 y los otros 50 a la clase 1.
*/
int main(int argc, char **argv)
{
  if(argc != 2)
    printf("\nNúmero de argumentos incorrecto\n\n"
           "FORMA DE COMPILACIÓN Y EJECUCIÓN:\n"
           "  $ gcc -Wall ejercicioC.c -o ejercicioC -lm\n"
           "  $ ./ejercicioC n\n\n"
           "Ejemplo:\n"
           "  $ ./ejercicioC 100\n\n"
  
           "  genera un conjunto de 100 datos donde la mitad corresponde a valores de la\n"
           "  clase 0 y los otros 50 a la clase 1.\n"
          ),exit(-1);

  int n = atoi(argv[1]);
  FILE *fd;

  fd = fopen("ejercicioC.names","w");
  fprintf(fd,"0,1.\n"
             "x1: continuous.\n"
             "x2: continuous.\n"
         );
  fclose(fd);

  fd = fopen("ejercicioC.data","w");
  imprimirPuntos(n/2,fd);
  fclose(fd);
  return 0;
}

double atan2(double x,double y);
double curva1(double x);
double curva2(double x);

/*
  impimirPuntos: Imprime en output los puntos generados. 
                 Se imprimen n de la clase 0 y n de la clase 1
  n: Número de puntos a generar de cada clase
*/
void imprimirPuntos(int n,FILE *output)
{
  int clase0 = n;
  int clase1 = n;
  
  srand48(time(NULL));

  double x,y;
  double ro,tetha;

  while(clase0+clase1){
    // inicio + longitud del intervalo*random()
    x = -1 + 2.0*drand48();
    y = -1 + 2.0*drand48();
    // Pasamos el punto generado a coordenadas polares
    ro = sqrt(pow(x,2)+pow(y,2));
    tetha = atan2(x,y);

    /*
      Bien, en este momento tenemos el punto que seleccionamos al azar pasado 
      a coordenadas polares 
      Para ver si el mismo corresponde a la clase 0 (si está entre las curvas 
      1 y 2) debemos considerar un detalle. Si sólo tomamos el ángulo tetha y 
      evaluamos curva1(tetha) <= ro <= curva2(tetha) estaremos aceptando los
      puntos que están en la clase cero restringidos a la primera vuelta de las
      curvas. Como las curvas dan tres giros hasta el radio 1 (por lo que se ve
      en la imagen de ejemplo y por experimentación mientras escribía el código)
      debemos considerar los puntos que satisfacen 
         curva1(tetha+2*pi) <= ro <= curva2(tetha+2*pi) o
         curva1(tetha+4*pi) <= ro <= curva2(tetha+4*pi) 
     
    */
    if(clase0){
      if(ro && ro <= 1){
        if(ro >= curva1(tetha) && ro <= curva2(tetha)){
          fprintf(output,"%f,%f,0\n",x,y);
          clase0--;
        } else if(ro >= curva1(2.0*M_PI + tetha) && ro <= curva2(2.0*M_PI + tetha)){
          fprintf(output,"%f,%f,0\n",x,y);
          clase0--;
        } else if(ro >= curva1(4.0*M_PI + tetha) && ro <= curva2(4.0 * M_PI + tetha)){
          fprintf(output,"%f,%f,0\n",x,y);
          clase0--; 
        } else 
          if(clase1){
             fprintf(output,"%f,%f,1\n",x,y);
             clase1--;
        }                    
      }
    } else if(clase1){
      if(
         !(ro >= curva1(tetha) && ro <= curva2(tetha)) &&
         !(ro >= curva1(2.0*M_PI + tetha) && ro <= curva2(2.0*M_PI + tetha)) &&
         !(ro >= curva1(4.0*M_PI + tetha) && ro <= curva2(4.0 * M_PI + tetha))
        ){
        fprintf(output,"%f,%f,1\n",x,y);
        clase1--;
      }
    }
  }
  return;
}


// Ley de la primer curva
double curva1(double x)
{
  return x/(4*M_PI);
}

// Ley de la segunda curva
double curva2(double x)
{
  return (x+M_PI)/(4*M_PI);
}

// Dadas las coordenadas cartesianas (x,y) obetenemos \tethe como resultado 
// NOTA: Se asume que x^2+y^2 es distinto de 0
//
// atan es la función arcotangente
//
// FUENTE: http://en.wikipedia.org/wiki/Polar_coordinate_system#Converting_between_polar_and_Cartesian_coordinates
//
double atan2(double x,double y)
{
  assert(pow(x,2)+pow(y,2));
  if(x > 0)
    return atan(y/x);
  if (x < 0 && y >= 0)
    return atan(y/x) + M_PI;
  if (x < 0 && y < 0)
    return atan(y/x) - M_PI;
  // De aquí en más x es igual a 0
  if (y > 0)
    return M_PI/2.0;
  // Como último caso x es 0 e y es negativo
  return -(M_PI/2.0);
}
