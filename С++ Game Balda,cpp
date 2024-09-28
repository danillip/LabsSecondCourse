#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

const int BOARD_SIZE = 5; // Размер игрового поля в игре "Балда"

// Функция для проверки, является ли слово допустимым ходом на данной конфигурации балды
bool isValidMove(const vector<vector<char>>& board, const string& word, int row, int col) {
    // Проверяем, находится ли слово полностью в пределах игрового поля
    if (row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE)
        return false;

    // Проверяем, не выходит ли слово за пределы игрового поля по горизонтали
    if (col + word.length() > BOARD_SIZE)
        return false;

    // Проверяем, не выходит ли слово за пределы игрового поля по вертикали
    for (int i = 0; i < word.length(); ++i) {
        if (row + i >= BOARD_SIZE)
            return false;
        // Проверяем, совпадает ли буква на доске с буквой в слове
        if (board[row + i][col] != '.' && board[row + i][col] != word[i])
            return false;
    }

    return true;
}

// Функция для вычисления очков за слово
int calculateScore(const string& word) {
    // Здесь можно определить логику подсчета очков за слово
    return word.length(); // Например, можно просто считать количество букв
}

// Функция для поиска лучшего хода с помощью бэктрекинга
void findBestMove(const vector<vector<char>>& board, const vector<string>& words, int moveLength, int& maxScore, vector<string>& bestMove, vector<string>& currentMove, unordered_set<string>& usedWords) {
    // Базовый случай: если длина текущего хода равна заданной длине
    if (moveLength == 0) {
        int totalScore = 0;
        for (const string& word : currentMove) {
            totalScore += calculateScore(word);
        }
        if (totalScore > maxScore) {
            maxScore = totalScore;
            bestMove = currentMove;
        }
        return;
    }

    // Перебираем все слова и все позиции на доске
    for (const string& word : words) {
        // Проверяем, использовали ли мы уже это слово
        if (usedWords.find(word) == usedWords.end()) {
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (isValidMove(board, word, i, j)) {
                        // Делаем ход
                        currentMove.push_back(word);
                        usedWords.insert(word);
                        // Рекурсивно ищем следующий ход
                        findBestMove(board, words, moveLength - 1, maxScore, bestMove, currentMove, usedWords);
                        // Отменяем ход
                        currentMove.pop_back();
                        usedWords.erase(word);
                    }
                }
            }
        }
    }
}

// Функция для вывода игрового поля с учетом размещенных на нем слов
void printBoardWithWords(const vector<vector<char>>& board, const vector<string>& words) {
    cout << "Board with words:" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] != '.') {
                cout << board[i][j] << " ";
            } else {
                bool isWordTile = false;
                for (const string& word : words) {
                    if (isValidMove(board, word, i, j)) {
                        cout << word[0] << " ";
                        isWordTile = true;
                        break;
                    }
                }
                if (!isWordTile) {
                    cout << ". ";
                }
            }
        }
        cout << endl;
    }
}

int main() {
    // Пример ввода данных: конфигурация балды и список слов
    vector<vector<char>> board = {
        {'.', '.', '.', '.', '.'},
        {'.', 'a', '.', '.', '.'},
        {'.', 'b', '.', '.', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.'}
    };
    vector<string> words = {"app", "abro", "ban"};

    int moveLength = 2; // Заданная длина последовательности ходов
    int maxScore = 0; // Максимальное количество очков
    vector<string> bestMove; // Лучшая последовательность ходов
    vector<string> currentMove; // Текущая последовательность ходов
    unordered_set<string> usedWords; // Использованные слова

    // Поиск лучшего хода
    findBestMove(board, words, moveLength, maxScore, bestMove, currentMove, usedWords);

    // Вывод результата
    cout << "Best move sequence:" << endl;
    for (const string& word : bestMove) {
        cout << word << " ";
    }
    cout << endl;
    cout << "Max score: " << maxScore << endl;

    // Вывод игрового поля с учетом размещенных на нем слов
    printBoardWithWords(board, bestMove);

    return 0;
}
