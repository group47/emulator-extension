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
cmp r2, r2 // set zero flag
addeq r5, r6, r7 // should add
cmn r3, r4
cmn r1, r2
sub r2, r2, r2
tst r2, r0
tst r11, r10
teq r2, r0
teq r3, r4
teq r7, r8