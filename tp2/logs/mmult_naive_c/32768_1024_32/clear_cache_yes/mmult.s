	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
$Ltext0:
	.cfi_sections	.debug_frame
	.align	2
	.globl	mmult
$LFB0 = .
	.cfi_startproc
	.set	nomips16
	.set	nomicromips
	.ent	mmult
	.type	mmult, @function
mmult:
	.frame	$fp,32,$31		# vars= 16, regs= 1/0, args= 0, gp= 8
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	.cfi_def_cfa_offset 32
	sw	$fp,28($sp)
	.cfi_offset 30, -4
	move	$fp,$sp
	.cfi_def_cfa_register 30
	sw	$4,32($fp)
	sw	$5,36($fp)
	sw	$6,40($fp)
	sw	$7,44($fp)
$LBB2 = .
	.loc 1 6 0
	sw	$0,8($fp)
	b	$L2
	nop

$L7:
$LBB3 = .
	.loc 1 7 0
	sw	$0,12($fp)
	b	$L3
	nop

$L6:
$LBB4 = .
	.loc 1 8 0
	sw	$0,16($fp)
	b	$L4
	nop

$L5:
	.loc 1 9 0 discriminator 3
	lw	$3,8($fp)
	lw	$2,44($fp)
	mul	$3,$3,$2
	lw	$2,12($fp)
	addu	$2,$3,$2
	sll	$2,$2,3
	lw	$3,40($fp)
	addu	$2,$3,$2
	lw	$4,8($fp)
	lw	$3,44($fp)
	mul	$4,$4,$3
	lw	$3,12($fp)
	addu	$3,$4,$3
	sll	$3,$3,3
	lw	$4,40($fp)
	addu	$3,$4,$3
	ldc1	$f2,0($3)
	.loc 1 10 0 discriminator 3
	lw	$4,8($fp)
	lw	$3,44($fp)
	mul	$4,$4,$3
	lw	$3,16($fp)
	addu	$3,$4,$3
	sll	$3,$3,3
	lw	$4,32($fp)
	addu	$3,$4,$3
	ldc1	$f4,0($3)
	lw	$4,16($fp)
	lw	$3,44($fp)
	mul	$4,$4,$3
	lw	$3,12($fp)
	addu	$3,$4,$3
	sll	$3,$3,3
	lw	$4,36($fp)
	addu	$3,$4,$3
	ldc1	$f0,0($3)
	mul.d	$f0,$f4,$f0
	.loc 1 9 0 discriminator 3
	add.d	$f0,$f2,$f0
	sdc1	$f0,0($2)
	.loc 1 8 0 discriminator 3
	lw	$2,16($fp)
	addiu	$2,$2,1
	sw	$2,16($fp)
$L4:
	.loc 1 8 0 is_stmt 0 discriminator 1
	lw	$3,16($fp)
	lw	$2,44($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L5
	nop

$LBE4 = .
	.loc 1 7 0 is_stmt 1 discriminator 2
	lw	$2,12($fp)
	addiu	$2,$2,1
	sw	$2,12($fp)
$L3:
	.loc 1 7 0 is_stmt 0 discriminator 1
	lw	$3,12($fp)
	lw	$2,44($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L6
	nop

$LBE3 = .
	.loc 1 6 0 is_stmt 1 discriminator 2
	lw	$2,8($fp)
	addiu	$2,$2,1
	sw	$2,8($fp)
$L2:
	.loc 1 6 0 is_stmt 0 discriminator 1
	lw	$3,8($fp)
	lw	$2,44($fp)
	sltu	$2,$3,$2
	bne	$2,$0,$L7
	nop

$LBE2 = .
	.loc 1 14 0 is_stmt 1
	nop
	move	$sp,$fp
	.cfi_def_cfa_register 29
	lw	$fp,28($sp)
	addiu	$sp,$sp,32
	.cfi_restore 30
	.cfi_def_cfa_offset 0
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	mmult
	.cfi_endproc
$LFE0:
	.size	mmult, .-mmult
$Letext0:
	.file 2 "/usr/lib/gcc/mips-linux-gnu/6/include/stddef.h"
	.section	.debug_info,"",@progbits
$Ldebug_info0:
	.4byte	0xe4
	.2byte	0x4
	.4byte	$Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	$LASF7
	.byte	0xc
	.4byte	$LASF8
	.4byte	$LASF9
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	$Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.4byte	$LASF10
	.byte	0x2
	.byte	0xd8
	.4byte	0x37
	.uleb128 0x4
	.byte	0x4
	.byte	0x7
	.4byte	$LASF0
	.uleb128 0x4
	.byte	0x8
	.byte	0x5
	.4byte	$LASF1
	.uleb128 0x4
	.byte	0x8
	.byte	0x4
	.4byte	$LASF2
	.uleb128 0x5
	.4byte	$LASF11
	.byte	0x1
	.byte	0x3
	.4byte	$LFB0
	.4byte	$LFE0-$LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xda
	.uleb128 0x6
	.ascii	"A\000"
	.byte	0x1
	.byte	0x3
	.4byte	0xda
	.uleb128 0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x6
	.ascii	"B\000"
	.byte	0x1
	.byte	0x3
	.4byte	0xda
	.uleb128 0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x7
	.4byte	$LASF3
	.byte	0x1
	.byte	0x4
	.4byte	0xda
	.uleb128 0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x6
	.ascii	"n\000"
	.byte	0x1
	.byte	0x4
	.4byte	0x2c
	.uleb128 0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x8
	.4byte	$LBB2
	.4byte	$LBE2-$LBB2
	.uleb128 0x9
	.4byte	$LASF4
	.byte	0x1
	.byte	0x6
	.4byte	0x2c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x8
	.4byte	$LBB3
	.4byte	$LBE3-$LBB3
	.uleb128 0x9
	.4byte	$LASF5
	.byte	0x1
	.byte	0x7
	.4byte	0x2c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x8
	.4byte	$LBB4
	.4byte	$LBE4-$LBB4
	.uleb128 0xa
	.ascii	"i\000"
	.byte	0x1
	.byte	0x8
	.4byte	0x2c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -16
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0xe0
	.uleb128 0x4
	.byte	0x8
	.byte	0x4
	.4byte	$LASF6
	.byte	0
	.section	.debug_abbrev,"",@progbits
$Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	$Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	$Ltext0
	.4byte	$Letext0-$Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
$Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
$LASF4:
	.ascii	"fila\000"
$LASF0:
	.ascii	"unsigned int\000"
$LASF10:
	.ascii	"size_t\000"
$LASF3:
	.ascii	"resultado\000"
$LASF6:
	.ascii	"double\000"
$LASF7:
	.ascii	"GNU C11 6.3.0 20170516 -meb -march=mips32r2 -mfpxx -mlls"
	.ascii	"c -mno-lxc1-sxc1 -mips32r2 -mabi=32 -g\000"
$LASF2:
	.ascii	"long double\000"
$LASF9:
	.ascii	"/root/tp2\000"
$LASF8:
	.ascii	"src/mult/mmult_naive_c.c\000"
$LASF11:
	.ascii	"mmult\000"
$LASF5:
	.ascii	"columna\000"
$LASF1:
	.ascii	"long long int\000"
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
