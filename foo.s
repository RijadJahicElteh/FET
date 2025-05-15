.section .data
  .align 3
d: .double 10.25
  
.section .text
.globl foo
foo:
  mtc1 $a0, $f0
  mtc1 $a2, $f4
  mtc1 $a3, $f5
  cvt.d.w $f0, $f0
  c.lt.d $f4, $f0
  bc1f elseif
  add.d $f0, $f0, $f4
  la $t0, d
  ldc1 $f6, ($t0)
  sub.d $f0, $f0, $f6
  jr $ra
elseif:
  c.eq.d $f4, $f0
  bc1f else
  add.d $f0, $f0, $f4
  jr $ra
else:
  add.d $f0, $f0, $f4
  la $t0, d
  ldc1 $f6, ($t0)
  add.d $f0, $f0, $f6
  jr $ra
