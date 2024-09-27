.model small
.stack 100h

.data
c db 1
d db 50
array db 10, 20, 30, 40, 55, 50 ; Массив элементов типа BYTE
array_length dw 6
count db 0

.code
start:
    mov ax, @DATA
    mov ds, ax

    ; Инициализация переменных
    mov cx, array_length ; Длина массива
    xor si, si           ; Индекс массива
    xor bl, bl           ; Счетчик подходящих элементов

next_elem:
    mov al, [array + si] ; Загружаем текущий элемент массива

    ; Проверка условия c <= a[i]
    cmp al, c
    jb not_in_range

    ; Проверка условия a[i] <= d
    cmp al, d
    ja not_in_range

    ; Увеличение счетчика, если элемент в диапазоне
    inc bl

not_in_range:
    ; Переход к следующему элементу
    inc si
    loop next_elem

    ; Сохранение результата
    mov count, bl

    ; Вывод результата
    mov al, count
    add al, '0' ; Преобразование в ASCII
    mov ah, 2
    int 21h

    ; Завершение программы
    mov ah, 4Ch
    int 21h

end start
