mov r0, #824
mov r1, #0x1100
mov r2, #0x0100
strh r1, [r0], #2
strh r2, [r0], #2
ldrh r3, [r0, #0]
ldrh r4, [r0, #2]
mov r1, #0x32
mov r2, #0xcc
mov r3, #0x88
mov r4, #0xff
strb r1, [r0], #1
strb r2, [r0], #1
strb r3, [r0], #1
strb r4, [r0], #-3
mov r1, #0
mov r2, #0
mov r3, #0
mov r4, #0
ldrb r1, [r0, #0]
ldrb r2, [r0, #1]!
ldrb r3, [r0, #1]!
ldrb r4, [r0, #1]!
ldrsb r1, [r0, #-3]!
ldrsb r2, [r0, #1]
ldrsb r3, [r0, #2]
ldrsb r4, [r0, #3]
stmda r13!, {r0-r4}
mov r0, #0
mov r1, #0
mov r2, #0
mov r3, #0
mov r4, #0
ldmib r13!, {r0-r4}
stmdb r13!, {r0-r4}
mov r0, #1
mov r1, #1
mov r2, #1
mov r3, #1
mov r4, #1
ldmia r13!, {r0-r4}
stmia r13!, {r0-r4}
mov r0, #2
mov r1, #2
mov r2, #2
mov r3, #2
mov r4, #2
ldmdb r13!, {r0-r4}
stmib r13!, {r0-r4}
mov r0, #3
mov r1, #3
mov r2, #3
mov r3, #3
mov r4, #3
ldmda r13!, {r0-r4}
mov r5, #14
mov r0, #0
mov r1, #0
mov r2, #0
mov r3, #0
mov r4, #0
mov r5, #0
mov r6, #0
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

.data
sec: .asciz "34oli 8olytr98yry8o4o4jshfifrog374tgufi78o4oli 8olytr98yry8o4o4jshfifrog374tgufi78oft3ogfo34o8gf8o4gfog55r44w8yfoherhfuerhukusegguvui8o358o4hyg38g5oh335484ry34u4u398490fuft3ogfo34o8gf8o4gfog55r44w8yfoherhfuerhukusegguvui8o358o4hyg38g5oh335484ry344oli 8olytr98yry84oli 8olytr98y4oli 8olytr98yry8o4o4jshfifrog374tgufi78oft3ogfo34o8gf8o4gfog55r44w8yfoherhfuerhukusegguvui8o358o4hyg38g5oh335484ry34u4u398490fury8o4o4jshfifrog374tgufi78oft3ogfo34o8gf8o4gfog55r44w8yfoherhfuerhukusegguvui8o358o4hyg38g5oh335484ry34u4u398490fuo4o4jshfifrog374tgufi78oft3ogfo34o8gf8o4gfog55r44w8yfoherhfuerhukusegguvui8o358o4hyg38g5oh335484ry34u4u398490fuu4u398490fu03"