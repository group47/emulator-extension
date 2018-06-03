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
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
mov r0, #0
