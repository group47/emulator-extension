mov r0, #0 // test for basic operation, overflow, borrow, 
mov r1, #0xffffffff //basic test for arithmatic operation
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
add r4, r2, r5 // no overflow
add r6, r2, r6 // no overflow
adc r5, r3, r7 // no overflow
adc r11, r6, r3 // no overflow
mov r0, #0             // basic test for arithmatic operation
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
sub r12, r12, r3 // no borrow
sub r9, r5, r4 // no borrow
sbc r7, r7, r3 // no borrow
sbc r6, r8, r5 // no borrow
mov r0, #0                 // basic test for logical operation
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
and r2, r2, r2
orr r7, r1, r7
eor r3, r3, r4
bic r3, r6, r9
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
add r2, r1, r2 //overflow
add r3, r1, r4 //overflow
adc r4, r1, r5 //overflow
adc r5, r1, r6 //overflow
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
sub r2, r0, r1 //borrow
sub r3, r4, r5 //borrow
sub r4, r7, r12 // borrow
sbc r4, r3, r11 //borrow
mov r0, #0
mov r1, #0xffffffff
mov r2, #2
mov r3, #2
mov r4, #2
mov r5, #2
mov r6, #6
mov r7, #7
mov r8, #8
mov r9, #9
mov r10, #10
mov r11, #11
mov r12, #12
rsb r0, r2, r1 // no borrow
rsb r0, r2, r3 // no borrow
rsc r3, r9, r12 // no borrow
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
rsb r0, r1, r2 // borrow
rsb r0, r3, r2 // borrow
rsc r3, r12, r9 // borrow
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
subs r2, r2, r2 // should set zero flag
addeq r5, r6, r7 //should add
addeqs r0, r2, r2 // should set zero flag
subs r10, r12, r11
addgt r5, r6, r7 // should execute
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
