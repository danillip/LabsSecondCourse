#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

vector<string> words = { "apple", "banana", "orange", "grape", "lemon" }; // Пример набора слов
unordered_set<string> wordSet(words.begin(), words.end());

int score(const string& word) {
	// Простой пример функции подсчета очков
	return word.size();
}

void findBestMove(const vector<vector<char>>& board, vector<vector<bool>>& visited, int x, int y, string currentWord, vector<string>& bestMove, int& bestScore) {
	if (wordSet.find(currentWord) != wordSet.end()) {
		int currentScore = score(currentWord);
		if (currentScore > bestScore) {
			bestScore = currentScore;
			bestMove.clear();
			bestMove.push_back(currentWord);
		}
		else if (currentScore == bestScore && find(bestMove.begin(), bestMove.end(), currentWord) == bestMove.end()) {
			bestMove.push_back(currentWord);
		}
	}

	if (currentWord.size() >= 5) {
		return; // Максимальная длина слова в "Балде"
	}

	// Массив смещений для проверки всех соседних клеток
	int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	for (int i = 0; i < 8; ++i) {
		int newX = x + dx[i];
		int newY = y + dy[i];

		if (newX >= 0 && newX < board.size() && newY >= 0 && newY < board[0].size() && !visited[newX][newY]) {
			visited[newX][newY] = true;
			findBestMove(board, visited, newX, newY, currentWord + board[newX][newY], bestMove, bestScore);
			visited[newX][newY] = false;
		}
	}
}

void printBestMove(const vector<vector<char>>& board) {
	int n = board.size();
	int m = board[0].size();

	vector<vector<bool>> visited(n, vector<bool>(m, false));
	vector<string> bestMove;
	int bestScore = 0;

	// Начать поиск лучшего хода с каждой клетки на доске
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			visited[i][j] = true;
			findBestMove(board, visited, i, j, string(1, board[i][j]), bestMove, bestScore);
			visited[i][j] = false;
		}
	}

	// Вывести лучший ход(ы) и его(их) очки
	cout << "Best Move(s) with score " << bestScore << ":\n";
	for (const auto& move : bestMove) {
		cout << move << endl;
	}
}

int main() {
	vector<vector<char>> board = {
		{'a', 'p', 'p', 'l', 'e'},
		{'b', 'a', 'n', 'a', 'n'},
		{'o', 'r', 'a', 'n', 'g'},
		{'e', 'g', 'r', 'a', 'p'},
		{'l', 'e', 'm', 'o', 'n'}
	};

	printBestMove(board);

	return 0;
}
