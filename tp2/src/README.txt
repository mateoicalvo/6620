El formato de entrada es una secuencia de lineas con el siguiente formato:

n a[1][1] a[1][2] ... a[n][n] b[1][1] b[1][2] ... b[n][n]

Es decir, cada linea contiene la dimensión de las matrices de n x n,
los elementos de a presentados en row major order, y los elementos de b
presentados en row major order. La linea termina en \n.

El parametro n y los elementos de a y b están separados por un espacio.

--

El formato de salida es:

n c[1][1] c[1][2] ... c[n][n]

Notar que en este caso, cada línea se compone de una sola matriz (producto
de 'a' y 'b').

--

Ejemplo:

Vamos a multiplicar las siguientes matrices:

1 0 0   1 2 3   1 2 3
0 1 0 x 4 5 6 = 4 5 6
0 0 1   7 8 9   7 8 9

$ cat input.txt 
3 1 0 0 0 1 0 0 0 1 1 2 3 4 5 6 7 8 9

$ ./mmult < input.txt 
3 1 2 3 4 5 6 7 8 9
