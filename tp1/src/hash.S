#include <sys/regdef.h>

    .abicalls
    .rdata
    #TODO: Acá iría el mensaje de error, en string, del assert.
    .align 0
mensaje_error_assert: .asciiz "Error en el assert\n"

    #TODO: El assert.

    .text
    .align 2
    .globl string_hash_more
    .ent string_hash_more

string_hash_more:
    #FIXME: .frame, puede no estar bien.
    .frame fp, 8, ra
    .set noreorder
    .cpload t9
    .set reorder

    subu sp, sp, 8
    .cprestore 0	#equivale sw gp, 0(sp)
	sw fp,4(sp)
    move fp,sp

    #En el ABA de la caller
    sw a0, 8(fp)	#direccion de sh esta en fp+8
	sw a1, 12(fp)	#direccion de str esta en fp+12
	sw a2, 16(fp)

    #TODO: ejecutar el assert.

    #Cargo sh->flag
    lb t0, 0(a0) #t0 = sh->flag

    #Cargo 1 en t1
    li t1, 1

    #si sh->flag != STRING_HASH_INIT salto al while
    bne t0, t1, while

    #sh->flag es STRING_HASH_INIT que es 1

    #cargo en t0 el valor STRING_HASH_MORE
    li t0, 2
    #modifico el struct, sh->flag = STRING_HASH_MORE
    sb t0, 0(a0)

    #recupero *str en t0
    lb t0, 0(a1)
    #Hago el sll y lo meto en t0
    sll t0, t0, 7		#(*str)<<7
    #Guardo ese valor en sh->hash
    sw t0, 4(a0)

    #preparo el while, len está en el ABA del caller
    #str también esta en el aba del caller.

    
    
    
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

    
    #str ya lo tengo
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
    #TODO: salida de funcion
    lw fp, 4(sp)
    addiu sp,sp,8
    jr ra

    .end string_hash_more