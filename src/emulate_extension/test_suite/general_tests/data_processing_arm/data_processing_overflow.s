mov r0, #0
mov r1, #0xffffffff
mov r2, #2
mov r3, #3
mov r4, #4
mov r5, #5
mov r6, #6
mov r7, #7
mov r8, #8
mov r9, #9
mov r10, #10
mov r11, #11
mov r12, #12
adds r2, r1, r2 //overflow
adds r3, r1, r4 //overflow
adcs r4, r1, r5 //overflow
adcs r5, r1, r6 //overflow
mov r0, #0
mov r1, #0xffffffff
mov r2, #2
mov r3, #2
mov r4, #2
mov r5, #5
mov r6, #6
mov r7, #7
mov r8, #8
mov r9, #9
mov r10, #10
mov r11, #11
mov r12, #12
mul r0, r2, r1 // overflow
mul r4, r5, r6 // no overflow
mla r0, r2, r3, r1 // overflow
mla r0, r10, r2, r9 // no overflow
mov r0, #0
mov r1, #0xffffffff
mov r2, #2
mov r3, #2
mov r4, #2
mov r5, #5
mov r6, #6
mov r7, #7
mov r8, #8
mov r9, #9
mov r10, #10
mov r11, #11
mov r12, #12
mvn r1, r1
cmp r1, r0 // should be zero
moveq r10, #10
movgt r11, #11
movls r12, #12
moval r1, r4
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r2
mov r5, r3
mov r5, r2
mov r5, r2
mov r5, r2