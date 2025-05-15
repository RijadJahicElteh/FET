.section .rodata
.globl str
str: .asciiz "p=%f\n"

.section .text
  .globl main
main:
  addiu $sp, $sp, -32
  sw $ra, 28($sp)
  lui $t0, 0x4123
  ori $t0, $t0, 0x3333
  sw $t0, 20($sp)
  addiu $a0, $sp, 20
  jal foo
  la $a0, str
  lwc1 $f4, 20($sp)
  cvt.d.s $f4, $f4
  mfc1 $a2, $f4
  mfc1 $a3, $f5
  jal printf
  lw $ra, 28($sp)
  addiu $sp, $sp, 32
  jr $ra

  
