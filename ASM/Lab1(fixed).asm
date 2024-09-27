; ƒл€ беззнаковых байт команды умножени€ и делени€ - mul div
; ƒл€    знаковых байт команды умножени€ и делени€ - imul idiv
.model small
 
.data
r db ? ; поставим первым, чтобы легче было найти при отладке
a db -25
d db -6
c db 0
 
.stack 100h
 
.code
start:
mov ax,@data
mov ds,ax
      
mov al,[c] ;al=5  
mov bl,2   ;cl=2
imul bl     ;2*c
 
; не об€зательно заносить число в регистр
; ¬место 2 команд можно написать sub al,[d]
; (и далее в нескольких местах то же)
mov cl,[d] ;cl=d=6
sub al,cl  ;bl=2*c-d
 
; xor bl, bl ;bl=0 не надо
mov bl,23  ;bl=23
add al,bl  ;al=2*c-d+23
 
mov cl,al  ; запомнить al в cl
 
mov al,[a] ;al=a
; ƒл€ процессора Intel 8086
; если делим на байт, то делимое всегда ax
; если делим на слово, то делимое всегда dx:ax
mov ah,0   ; дл€ беззнаковых байт. ƒл€ байт со знаком - команда cbw    
cbw
mov bl,4   ;bl=4               
idiv bl     ;al=a/4 ah=a mod 4
; xor dl,dl не надо
mov dl,1   ;dl=1
sub al,dl  ;al=a/4 - 1   
xchg cl,al ; помен€ть местами, чтобы в al было делимое, а в cl - делитель
mov ah,0   ; дл€ беззнаковых байт. ƒл€ байт со знаком - команда cbw  
cbw
idiv cl     ;al=(2*c-d+23)/(a/4-1),ah=остаток от делени€
 
mov [r],al   ;r=al
 
mov ah,4Ch
mov al,00h
int 21h
end start