.model small
.stack 100h

.data
c db 1
d db 50
array db 10, 20, 30, 40, 55, 50 ; ������ ��������� ���� BYTE
array_length dw 6
count db 0

.code
start:
    mov ax, @DATA
    mov ds, ax

    ; ������������� ����������
    mov cx, array_length ; ����� �������
    xor si, si           ; ������ �������
    xor bl, bl           ; ������� ���������� ���������

next_elem:
    mov al, [array + si] ; ��������� ������� ������� �������

    ; �������� ������� c <= a[i]
    cmp al, c
    jb not_in_range

    ; �������� ������� a[i] <= d
    cmp al, d
    ja not_in_range

    ; ���������� ��������, ���� ������� � ���������
    inc bl

not_in_range:
    ; ������� � ���������� ��������
    inc si
    loop next_elem

    ; ���������� ����������
    mov count, bl

    ; ����� ����������
    mov al, count
    add al, '0' ; �������������� � ASCII
    mov ah, 2
    int 21h

    ; ���������� ���������
    mov ah, 4Ch
    int 21h

end start
