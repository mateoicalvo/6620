#include <sys/regdef.h>
#include <sys/syscall.h>

#include "hash.h"

    .abicalls
    .rdata
    .align 0

mensaje_error_assert: .asciiz "Error en el assert\n"
longitud_msj_error: .word 19

    .text
    .align 2
    .globl string_hash_more
    .ent string_hash_more

    .extern STRING_HASH_INIT
    .extern STRING_HASH_MORE

string_hash_more:
    .frame fp, 8, ra
    .set noreorder
    .cpload t9
    .set reorder

    subu sp, sp, 8
    .cprestore 0
	sw fp,4(sp)
    move fp,sp

    #En el ABA de la caller
    sw a0, 8(fp)	#direccion de sh esta en fp+8
	sw a1, 12(fp)	#direccion de str esta en fp+12
	sw a2, 16(fp)   #direccion de len esta en fp+16

    lw t2, 8(fp) 	#t2=direccion de sh
    lb t0, 0(t2)

    li t1, STRING_HASH_INIT

    #si sh->flag == STRING_HASH_INIT salto a flag_init
    beq t0, t1, flag_init

    li t1,STRING_HASH_MORE
    #si sh->flag == STRING_HASH_MORE salto al while
    beq t0, t1, while

assertion_fail:
    li a0,2	
    la a1, mensaje_error_assert
    lw a2, longitud_msj_error
    li v0, SYS_write
    syscall
    li v0, SYS_exit
    syscall


flag_init:
    li t0, STRING_HASH_MORE
    #modifico el struct, sh->flag = STRING_HASH_MORE
    sb t0, 0(t2)

    #recupero *str en t0
    # cargar 12(fp) y hago lb
    lw t2, 12(fp)
    lb t0, 0(t2)

    #(*str)<<7
    sll t0, t0, 7		
    #Guardo ese valor en sh->hash
    sw t0, 4(a0)

while:
    #str en t0
    lw t0, 12(fp)
    # len en t1
    lw t1, 16(fp)

    #recupero en t2 *str (un char)
    lb t2, 0(t0)
    beqz t2, salir

    #evaluo len:
    beqz t1, salir
    #decremento y actualizo len
    addi t1, t1, -1
    sw t1, 16(fp)

    #En t3 cargo el primo
    li t3, 1000003
    #En t4 recupero el valor de sh->hash
    lw t4, 4(a0)
    #En t5 multiplico
    mul t5, t4, t3
    #*str ya lo tengo en t2
    #en t6 hago el xor
    xor t6, t5, t2
    #Actualizo el valor de sh->hash
    sw t6, 4(a0)
    
    #incremento str (el puntero).
    addiu t0, t0, 1
    sw t0, 12(fp)   

    #En t7 cargo sh->size
    lw t7, 8(a0)
    #incremento y guardo
    addiu t7, t7, 1
    sw t7, 8(a0)

    j while


salir:
    lw fp, 4(sp)
    addiu sp,sp,8
    jr ra
    
    .end string_hash_more
