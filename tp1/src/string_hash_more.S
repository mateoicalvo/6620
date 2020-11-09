#string_hash_more.S

#include <sys/regdef.h>
#include <sys/syscall.h>


	.text 		#arrancamos con el segmento de texto
	.abicalls	#directiva generada por el compilador, indica 
			#vamos a respetar las llamadas de la abi. No
			#es necesario pero creo aporta info al debugger
	.align 2	#alineamos la instruccion a multiplo de 4
    .ent string_hash_more
    .globl string_hash_more

string_hash_more:
	.frame fp,8,ra	#puse 8 porque es la cantidad de bytes que 
			#me parece va a ocupar el stack frame
	.set noreorder
	.cpload t9
	.set reorder

#creo el stack frame

	subu sp,sp,8	#es una funcion non-leaf, por lo que no vamos
			#a necesitar el ABA, y por lo visto en la funcion
			#de ejemplo no hay variables locales declaradas
			#entonces la cantidad de cosas que guardamos es 
			#el fp y el gp de la SRA
	.cprestore 0	#equivale sw gp, 0(sp)
	sw fp,4(sp)

	move fp,sp	#Aca el frame pointer coincide con la base del 
			#del stack

#la funcion tiene 3 argumentos: dos punteros un size_t
#estos nos los pasan en los registros de $a0 - $a3
#voy cargando entonces los valores en la ABA de la funcion caller

	sw a0, 8(fp)	#direccion de sh esta en fp+8
	sw a1, 12(fp)	#direccion de str esta en fp+12
	sw a2, 16(fp)	#len esta en fp+16
#en teoria todo ocupa <= a un word, no deberia haber problemas

#ahora hay que hacer el assert
#tengo la direccion de memoria en la que esta el sh, necesito
#acceso a sh->flag. Por lo visto en el header, el primer atributo
#de sh es el flag que se necesita, entonces puedo acceder usando 
#la misma direccion guardada, con tamaño de un word


#aca tengo la duda de si esta bien que no estoy recuperando el valor
# de la ABA del caller
#Estoy cargando lo que se pide directamente

	lb t0,0(a0)	#t0 = memoria[$a0 + 0]
	
#hacemos ahora las comparaciones del assert
	li t5, 2
	beq t0, t5, WHILE	#if sh->flag == 1 salta a WHILE

	li t6, 1
#si llega aca no se cumplio la primer comparacion
	bne t0, t6 ,FALLO_ASSERT	#segunda comparacion

#llego aca, t0 == STRING_HASH_INIT
HASH_INIT:
	add t1,zero,1		#t1 = 1 = STRING_HASH_MORE
	addiu t2, a0, 0		#t2 = direccion de sh
	sb t1, 0(t2)		#h->flag= t1 = 1
	addiu t3, a1, 0		#t3= direccion de str
	lb t1, 0(a1) 		#t1= str
	sll t5, t1, 7		#(*str)<<7
	sw t5, 4(t2)		#sh->hash = (*str)<<7
	lw t4, 16(fp)		#t4 = len


# En t5 pongo str
# En t6 pongo *str

addiu t5, a1, 0
lb t6, 0(a1)

WHILE:
	beq t6, zero, RETURN	#anda a return si el char es cero
	beqz t4,RETURN		#anda a return si len ==0 // No deberia dar la vuelta

	addi t4,t4,-1		#len--
	
	li t0, 1000003		#load inmediate. t0=1000003

	lw t3, 4(a0)		#t3 = sh->hash
	mul t3,t0,t3		#t3= 1000003 * sh->hash
	
	# el xor, luego el inc.
	xor t3,t3,t6		#el xor entre sh++ y lo otro
	addiu t5, t5, 1 #inc puntero
	lb t6, 0(t5) # refresco char
	
	#add t1,t1,1		#*str++ #FIXME: esto esta mal
	sw t3,4(a0)		#sh->hash = t3
	lw t3,8(a0)		#t3= sh->size
	add t3,t3,1		#t3=t3+1
	sw t3,8(a0)		#sh->size= sh->size +1
	j WHILE


RETURN:
	
	lw fp,4(sp)		#recupero el fp original
	addiu sp,sp,8		#destruyo el stack frame
	jr ra


FALLO_ASSERT:
	li v0,SYS_exit
	syscall
	j RETURN  

.end string_hash_more

