.model small
.stack 100h

.data
a dw 20
b dw 10
X dw 0

.code
start:   
mov ax,@data
mov ds,ax

mov ax, [a]       ; AX = a       
mov bx, [b]       ; BX = b

cmp ax,bx       ; a-b и далее работаем с условными переходами jg jl je
jg a_bolshe_b 
je A_equal_to_B
jl a_menshe_b

a_bolshe_b:           
; IF A > B, X = (A - B) / (A) + 1
mov ax,[a]
sub ax,[b]
mov dx,0       ; „истим dx дл€ div
mov bx,[a]
cwd
idiv bx        ; AX = (A - B) / (A) + 1    
add ax,1
mov X, ax
jmp exit   

A_equal_to_B:
; If a = b, x =25
mov ax,25  
mov X,ax
jmp exit

a_menshe_b:
; IF A < B, X = (A - 5) / B   
mov ax,[a]
sub ax,5
mov dx,0
mov bx,[b]      ;clear Dx for DIV
cwd
idiv bx         ; AX = (A - 5) / B
mov X, ax
jmp exit

exit:
mov ah, 4Ch    
int 21h
end start