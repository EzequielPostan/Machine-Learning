// test3: 
//  Código Scilab para graficar el resultado del test3, está escrito para el
//  caso de 20000 casos de prueba (n=20000). Si se desea modificar esta 
//  cantidad se debe altirar el valor de n
//

clear()

n = 20000

[fd,err] = mopen("ejercicioC.data",'r')
for i=1:n
  [n,A(i,1),A(i,2),A(i,3)] = mfscanf(fd,"%f,%f,%d.");
  if A(i,3) == 1 then
    C(i,1) = A(i,1);
    C(i,2) = A(i,2);
  else
    B(i,1) = A(i,1);
    B(i,2) = A(i,2);
  end
end

mclose(fd)

plot(C(:,1),C(:,2),'dr')
plot(B(:,1),B(:,2),'dg')
