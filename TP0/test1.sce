//  test1.sce
//  Código Scilab para corrobarar los resultados de los ejercicios a) y b)
//  con un test de dimensión 2 y 200 casos de prueba (n=200 d=2)
//
//  Si se desea tenes más casos de prueba, modificar el valor de n_div_2
//  (el mismo debe ser igual a la cantidad de datos de cada clase, n/2)
//

clear()

n_div_2 = 100

[fd,err] = mopen("ejercicioA.data",'r')
for i=1:n_div_2
  [n,A(i,1),A(i,2),A(i,3)] = mfscanf(fd,"%f,%f,%d");
end

for i=1:n_div_2
  [n,B(i,1),B(i,2),B(i,3)] = mfscanf(fd,"%f,%f,%d");
end

mclose(fd)

length(A)
length(B)

mean(A,'r')
stdev(A,'r')

mean(B,'r')
stdev(B,'r')

clf()
plot(A(:,1),A(:,2),'db')
plot(B(:,1),B(:,2),'dr')

histplot(10,A(:,1))
histplot(10,A(:,2))
histplot(10,B(:,1))
histplot(10,B(:,2))
