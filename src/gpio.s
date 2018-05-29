
ldr r0,=0x9249249 # write pattern
ldr r1,=0x20200008 # where to write r0
ldr r2,=0x20200028 # where to write r3
ldr r3,=0x00400000 # what to write to clear
ldr r4,=0x2020001C #where to write to turn on

str r0, [r1, #0]
str r3, [r2, #0]
str r3, [r4, #0]

loop:
b loop