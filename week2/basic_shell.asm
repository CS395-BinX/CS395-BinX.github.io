section .text ; Text section for code
global _start ; Begins execution at _start
_start:

mov rax, 59 ; Syscall for execve
xor rbx, 0 ; Sets RBX to NULL
push rbx ; Pushes a string terminator onto the stack
mov rbx, 0x68732f6e69622f ; Moves "/bin/sh" (written in ASCII) to RBX
push rbx ; Push "/bin/sh" onto the stack
mov rdi, rsp ; Get a pointer to "/bin/sh" in RDI
mov rsi, 0 ; Sets RSI to NULL
mov rdx, 0 ; Sets RDX to NULL
syscall ; Does the actual system interrupt
