#include <iostream>
#include <vector>
#include <algorithm>

/*
3 
3 5 1 1 1 1 1 
4 2 161 5 
4 7 8 2 9 17 4 4 10 
*/
 
int main() {
    int numTests;
    std::cin >> numTests; // Читаем количество тестов

    for (int i = 0; i < numTests; ++i) {
        int t, n;
        std::cin >> t >> n; // Читаем время t и количество подпроектов n

        std::vector<int> values(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> values[j]; // Читаем стоимости подпроектов
        }

        // Сортируем стоимости в порядке убывания
        std::sort(values.begin(), values.end(), std::greater<int>());

        // Выбираем первые t самых дорогих подпроектов и суммируем их
        int maxProfit = 0;
        for (int j = 0; j < t && j < n; ++j) {
            maxProfit += values[j];
        }

        // Выводим максимальную заработанную сумму
        std::cout << maxProfit << std::endl;
    }

    return 0;
}