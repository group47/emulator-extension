ldr r1, =msg
ldrh r2, [r1, #0]
ldrh r3, [r1, #2]
mov r4, #0x11000101
strh r4, [r2]
strh r4, [r2, #2]
ldrh r3, [r1, #2]
ldr r5, =num
ldrsb r6, [r5, #0]
ldrsb r7, [r5, #1]
ldrsb r8, [r5, #2]
ldrsb r9, [r5, #3]
strsb r6, [r5, #4]
strsb r7, [r5, #5]
strsb r8, [r5, #6]
strsb r9, [r5, #7]
strsb r6, [r5, #4]!
mov r0, #0
mov r1, #0
mov r2, #0
mov r3, #0
mov r4, #0
mov r5, #0
mov r6, #0
mov r7, #0
mov r8, #0
mov r9, #0
mov r0, #10
mov r1, #-12
ldr r2, =msg
ldr r3, =num
stmia r13!, {r0-r3, r14}
mov r0, #0
mov r1, #0
mov r2, #0
mov r3, #0
ldmdb r13!, {r0-r3, r14}
mov r0, #0
mov r1, #0
mov r2, #0
mov r3, #0
mov r4, #0
mov r5, #0
mov r6, #0
mov r7, #0
mov r8, #0
mov r9, #0
mov r0, #10
mov r1, #-12
ldr r2, =msg
ldr r3, =num
b somefun
bl somefun
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
somefun:
stmia r13!, {r0-r3, r14}
mov r0, #1
mov r1, #1
mov r2, #1
mov r3, #1
ldmdb r13!, {r0-r3, r15}
.data
num: .int 0x01ff, 0
msg: .asciz "helloworldelloworlelloworlelloworllowolowolowolowolowolowolowowolowolowowolowoloowolowoloowolowolowhelloworldellohelloworldellowwo"
len = .-msg
