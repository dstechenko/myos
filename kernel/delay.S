.globl cdelay
cdelay:
  subs x0, x0, #1
  bne delay
  ret
