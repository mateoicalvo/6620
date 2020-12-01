#include <sys/regdef.h>

    .abicalls
    .text
    .align 2
    .set oddspreg
    .globl mmult
    .ent mmult

mmult:
    .frame fp, 8, ra
    .set noreorder
    .cpload t9
    .set reorder

    subu sp, sp, 8
    .cprestore 0
	sw fp, 4(sp)
    move fp, sp

    #En el ABA de la caller
    sw a0, 8(fp)  #matriz_t* A esta en fp+8
	sw a1, 12(fp) #matriz_t* B esta en fp+12
	sw a2, 16(fp) #matriz_t* C esta en fp+16
    sw a3, 20(fp) #dimension (n) esta en fp+20
    
    li t3, 0   #t3 = 0 (fila)
iter_filas:
    beq t3, a3, salir #fila == n?
    li t4, 0           #t4 = 0 (columna)
    iter_columnas:
        beq t4, a3, inc_fila    #columna == n?
        li t5, 0                   #t5 = 0 (i)
        mtc1 zero, $f6 #f6 vale cero, aca guardo sumas parciales
        mtc1 zero, $f7 #f7 seteado a cero porque trabajo con doubles
        iter_n:
            beq t5, a3, inc_columna #i == n? -> columna ++
            mul t6, a3, t3  #t6 = fila * n
            add t6, t6, t5  #t6 es fila*n + i, t6 es indice de A

            sll t0, t6, 3   #t0 = t6 * 8
            add t0, a0, t0  #t0 tiene la direccion de A[t6]
            ldc1 $f0, 0(t0) #f0 tiene el elemento de A

            mul t7, t5, a3  #t7 = i * n
            add t7, t7, t4  #t7 es i*n + columna, t7 es indice de B

            sll t1, t7, 3   #t1 = t7 *8
            add t1, a1, t1  #t1 tiene la direccion de B[t6]
            ldc1 $f2, 0(t1) #f2 tiene el elemento de B

            madd.d $f6, $f6, $f2, $f0 #f6 tiene A[i, j]*B[j, i] + A[i-1, j-1]*B[j-1, i-1] + ...
            
            addi t5, t5, 1
            j iter_n
        inc_columna:
        #Luego de iterar la fila de A y la columna de B, guardo en
        # C[ij] la suma acumulada.
        mul t8, t3, a3  #t8 = fila * n
        add t8, t8, t4  #t8 es fila*n + columna es indice de C
        sll t2, t8, 3   #t2 = t8*8
        add t2, a2, t2  #t2 tiene la direccion de C[t8]
        sdc1 $f6, 0(t2)
        addi t4, t4, 1
        j iter_columnas
    inc_fila:
    addi t3, t3, 1
    j iter_filas

salir:
    lw fp, 4(sp)
    addiu sp,sp,8
    jr ra
    
    .end mmult
