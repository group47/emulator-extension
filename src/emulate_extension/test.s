.text
.global _start
_start:
    mov r7, #45
    mov r0, #0 // r0 now contains the program break
    svc 0
    mov r1, r0
    mov r0, #100
    svc 0 // actually allocate the memory 
    mov r3, #0xffffffff
    cmp r0, r3
    beq message
    mov r9, #10
    str r9, [r0]
label:
    mov r7, #1
    svc 0
message:
    ldr r1, =msg
    ldr r2, =len
    mov r7, #4
    svc 0

.data 
    msg: .asciz "allocate memory is not successful\n"
    len = .-msg

