#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100;

// Массив для хранения результатов динамического программирования
long long dp[MAXN + 1][MAXN + 1][MAXN + 1];

void precompute() {
    // Базовый случай: один дом виден и слева, и справа
    dp[1][1][1] = 1;
    
    // Заполнение таблицы dp
    for (int n = 2; n <= MAXN; ++n) {
        for (int left = 1; left <= n; ++left) {
            for (int right = 1; right <= n; ++right) {
                // Если новый дом самый высокий, три варианта:
                dp[n][left][right] = (n - 2) * dp[n - 1][left][right] // в середину
                                  + dp[n - 1][left - 1][right]       // на первое место
                                  + dp[n - 1][left][right - 1];      // на последнее место
            }
        }
    }
}

int main() {
    // Предварительное вычисление всех значений
    precompute();

    // Ввод и обработка каждого теста
    int n, leftSide, rightSide;
    while (cin >> n >> leftSide >> rightSide) {
        cout << dp[n][leftSide][rightSide] << endl;
    }

    return 0;
}
