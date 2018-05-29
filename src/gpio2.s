ldr r0,=0x9249249
ldr r1,=0x20200008
ldr r2,=0x20200028
ldr r3,=0x00400000
ldr r4,=0x2020001C
str r0, [r1, #0 ]
str r3, [r2, #0 ]
str r3, [r4, #0 ]
loop:
b loop
andeq r0, r0, r0