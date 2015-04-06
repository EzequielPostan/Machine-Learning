//  test2.sce
//  Código Scilab para corrobarar los resultados de los ejercicios a) y b)
//  con un test de dimensión 4 y 2000 casos de prueba (n=2000 d=4)
//
//  Si se desea tenes más casos de prueba, modificar el valor de n_div_2
//  (el mismo debe ser igual a la cantidad de datos de cada clase, n/2)
//

clear()

n_div_2 = 1000

[fd,err] = mopen("ejercicioB.data",'r')
for i=1:n_div_2
  [n,A(i,1),A(i,2),A(i,3),A(i,4),A(i,5)] = mfscanf(fd,"%f,%f,%f,%f,%d");
end

for i=1:n_div_2
  [n,B(i,1),B(i,2),B(i,3),B(i,4),B(i,5)] = mfscanf(fd,"%f,%f,%f,%f,%d");
end

mclose(fd)

length(A)
length(B)

mean(A,'r')
stdev(A,'r')

mean(B,'r')
stdev(B,'r')
