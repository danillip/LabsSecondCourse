#include <stdio.h>
#include "math_operations.h"

int main() {
    int m, n;
    
    printf("Введите m и n: ");
    if (scanf("%d %d", &m, &n) != 2 || m <= 0 || n <= 0) {
        printf("Ошибка: некорректный ввод. Пожалуйста, введите положительные целые числа для m и n.\n");
        return 1;
    }

    if (m > n) {
        int temp = m;
        m = n;
        n = temp;
    }

    int result = calculate_difference(m, n);
    if (result == -1) {
        printf("В диапазоне от %d до %d нет полных квадратов.\n", m, n);
    } else {
        printf("Разность наибольшего и наименьшего полных квадратов: %d\n", result);
    }

    return 0;
}

