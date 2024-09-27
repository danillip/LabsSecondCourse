#include "math_operations.h"
#include <stdio.h>
#include <math.h>

int is_square(int n) {
    int root = sqrt(n);
    return root * root == n;
}

int calculate_difference(int m, int n) {
    int min_square = -1, max_square = -1;

    for (int i = m; i <= n; i++) {
        //printf("Проверяем значение: %d\n", i); 
        if (is_square(i)) {
            if (min_square == -1 || i < min_square)
                min_square = i;
            if (max_square == -1 || i > max_square)
                max_square = i;
        }
    }

    if (min_square == -1 || max_square == -1)
        return -1;

    return max_square - min_square;
}

