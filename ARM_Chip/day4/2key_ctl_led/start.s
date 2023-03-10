.global _start

_start:
    ldr sp, =0x40008000
    bl main
stop:
    b stop
    