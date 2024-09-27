; ��� ����������� ���� ������� ��������� � ������� - mul div
; ���    �������� ���� ������� ��������� � ������� - imul idiv
.model small
 
.data
r db ? ; �������� ������, ����� ����� ���� ����� ��� �������
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
 
; �� ����������� �������� ����� � �������
; ������ 2 ������ ����� �������� sub al,[d]
; (� ����� � ���������� ������ �� ��)
mov cl,[d] ;cl=d=6
sub al,cl  ;bl=2*c-d
 
; xor bl, bl ;bl=0 �� ����
mov bl,23  ;bl=23
add al,bl  ;al=2*c-d+23
 
mov cl,al  ; ��������� al � cl
 
mov al,[a] ;al=a
; ��� ���������� Intel 8086
; ���� ����� �� ����, �� ������� ������ ax
; ���� ����� �� �����, �� ������� ������ dx:ax
mov ah,0   ; ��� ����������� ����. ��� ���� �� ������ - ������� cbw    
cbw
mov bl,4   ;bl=4               
idiv bl     ;al=a/4 ah=a mod 4
; xor dl,dl �� ����
mov dl,1   ;dl=1
sub al,dl  ;al=a/4 - 1   
xchg cl,al ; �������� �������, ����� � al ���� �������, � � cl - ��������
mov ah,0   ; ��� ����������� ����. ��� ���� �� ������ - ������� cbw  
cbw
idiv cl     ;al=(2*c-d+23)/(a/4-1),ah=������� �� �������
 
mov [r],al   ;r=al
 
mov ah,4Ch
mov al,00h
int 21h
end start