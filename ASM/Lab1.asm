.model tiny
org 100h

INCLUDE emu8086.inc

DEFINE_PRINT_STRING
DEFINE_SCAN_NUM
DEFINE_PRINT_NUM
DEFINE_PRINT_NUM_UNS

.data
    ENTER_A_MSG db "Enter A: ", 0
    ENTER_C_MSG db "Enter C: ", 0
    ENTER_D_MSG db "Enter D: ", 0
    RESULT_MESSAGE db "(2*c-d+23)/(a/4-1) = ", 0

.code
    ; Enter A
    lea si, ENTER_A_MSG
    call print_string
    call scan_num
    PRINTN ''
    mov bx, cx ; сохраняем a в bx

    ; Enter C
    lea si, ENTER_C_MSG
    call print_string
    call scan_num
    PRINTN ''
    mov ax, cx ; сохраняем c в ax

    ; умножаем c на 2
    shl ax, 1
    push ax

    ; Enter D
    lea si, ENTER_D_MSG
    call print_string
    call scan_num
    PRINTN ''
    mov dx, cx ; сохраняем d в dx

    ; 2*c - d
    pop ax
    sub ax, dx

    ; прибавляем 23
    add ax, 23

    ; a/4
    mov cx, bx
    shr cx, 2

    ; вычитаем 1
    sub cx, 1

    ; делаем деление ax на cx
    xor dx, dx
    cwd
    idiv cx

    ; выводим результат
    lea si, RESULT_MESSAGE
    call print_string
    call print_num
    ret
