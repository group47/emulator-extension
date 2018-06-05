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
adds r12, r2, r3 // normal
adcs r12, r2, r3
adds r12, r1, r2 // overflow
adcs r12, r1, r9
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
subs r2, r2, r2 // should set zero flag
subs r10, r12, r11
