//-----------------------------------------------
.set noat
.set noreorder

.global ENTRYPOINT
.global _start
.global _exit
.global __main

//-----------------------------------------------
.ent	_start
.text				# 0x00200000
nop
nop
ENTRYPOINT:
_start:

// clear .bss
zerobss:
	lui	$2, %hi(_fbss)
	lui	$3, %hi(_end)
	addiu	$2, $2, %lo(_fbss)
	addiu	$3, $3, %lo(_end)
1:
	nop
	nop
	sq	$0, ($2)
	sltu	$1, $2, $3
	bne	$1, $0, 1b
	addiu	$2, $2, 16

// initialize main thread
	lui	$4, %hi(_gp)
	lui	$5, %hi(_stack)
	lui	$6, %hi(_stack_size)
	lui	$7, %hi(_args)
	lui	$8, %hi(_root)
	addiu	$4, $4, %lo(_gp)
	addiu	$5, $5, %lo(_stack)
	addiu	$6, $6, %lo(_stack_size)
	addiu	$7, $7, %lo(_args)
	addiu	$8, $8, %lo(_root)
	move	$28, $4
	addiu	$3, $0, 60
	syscall
	move	$29, $2

// initialize heap area
	lui	$4, %hi(_end)
	lui	$5, %hi(_heap_size)
	addiu	$4, $4, %lo(_end)
	addiu	$5, $5, %lo(_heap_size)
	addiu	$3, $0, 61
	syscall

// flush data cache
	move	$4, $0
	jal	ps2_flush_cache
	nop

// call main program
	ei
	lui	$2, %hi(_args)
	addiu	$2, $2, %lo(_args)
	lw	$4, ($2)
	jal	main
	addiu	$5, $2, 4

	j	Exit
	move	$4, $2
.end	_start

//-----------------------------------------------
.align	3
.ent	_exit
_exit:
	j	Exit
	move	$4, $0
.end	_exit
    
//-----------------------------------------------
.align	3
.ent	_root
_root:
	addiu	$3, $0, 35		# ExitThread();
	syscall
.end	_root

//-----------------------------------------------
.align	3
.ent	__main
__main:
	jr	$31
	nop
.end	__main

//-----------------------------------------------
Exit:
	li	$3,4
	syscall
	jr	$31
	nop

//-----------------------------------------------
.bss
.align	6
_args: .space	256 + 16*4 + 1*4
