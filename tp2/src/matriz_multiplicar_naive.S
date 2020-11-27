#include <sys/regdef.h>

    .abicalls
    .text
    .align 2
    .globl matriz_multiplicar_naive
    .ent matriz_multiplicar_naive

matriz_multiplicar_naive:
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

            mul.d $f0, $f0, $f2 #f2 tiene A[ij]*B[ji]
            
            mul t8, t3, a3  #t8 = fila * n
            add t8, t8, t4  #t8 es fila*n + columna t8 es indice de C

            sll t2, t8, 3   #t2 = t8*8
            add t2, a2, t2  #t2 tiene la direccion de C[t8]
            ldc1 $f4, 0(t2) #f4 tiene el elemento de C (parcial)

            add.d $f4, $f0, $f4
            sdc1 $f4, 0(t2)

            addi t5, t5, 1
            j iter_n
        inc_columna:
        addi t4, t4, 1
        j iter_columnas
    inc_fila:
    addi t3, t3, 1
    j iter_filas

salir:
    lw fp, 4(sp)
    addiu sp,sp,8
    jr ra
    
    .end matriz_multiplicar_naive
