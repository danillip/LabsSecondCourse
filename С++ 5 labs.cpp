#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/* Верный
4 3 
1 2 50
1 3 90
2 4 20
*/

/* Не Верный
4 3 
1 2 50
1 3 120
2 4 150
*/

const int INF = 1000000000; // Используемое значение бесконечности

void floydWarshall(vector<vector<int>>& dist, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

bool isReachableWithin100Km(const vector<vector<int>>& dist, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && dist[i][j] > 100) {
                return false;
            }
        }
    }
    return true;
}

bool canReachAllCitiesWithin100Km(vector<vector<int>>& dist, int n) {
    floydWarshall(dist, n);
    if (isReachableWithin100Km(dist, n)) {
        return true;
    }
    
    // Проверяем возможность добавления до трех дорог
    vector<pair<int, int>> edges;
    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (dist[u][v] > 100) {
                edges.emplace_back(u, v);
            }
        }
    }

    int numEdges = edges.size();
    for (int i = 0; i < numEdges; ++i) {
        for (int j = i + 1; j < numEdges; ++j) {
            for (int k = j + 1; k < numEdges; ++k) {
                vector<vector<int>> newDist = dist;
                newDist[edges[i].first][edges[i].second] = 100;
                newDist[edges[i].second][edges[i].first] = 100;
                newDist[edges[j].first][edges[j].second] = 100;
                newDist[edges[j].second][edges[j].first] = 100;
                newDist[edges[k].first][edges[k].second] = 100;
                newDist[edges[k].second][edges[k].first] = 100;
                floydWarshall(newDist, n);
                if (isReachableWithin100Km(newDist, n)) {
                    return true;
                }
            }
        }
    }

    for (int i = 0; i < numEdges; ++i) {
        for (int j = i + 1; j < numEdges; ++j) {
            vector<vector<int>> newDist = dist;
            newDist[edges[i].first][edges[i].second] = 100;
            newDist[edges[i].second][edges[i].first] = 100;
            newDist[edges[j].first][edges[j].second] = 100;
            newDist[edges[j].second][edges[j].first] = 100;
            floydWarshall(newDist, n);
            if (isReachableWithin100Km(newDist, n)) {
                return true;
            }
        }
    }

    for (int i = 0; i < numEdges; ++i) {
        vector<vector<int>> newDist = dist;
        newDist[edges[i].first][edges[i].second] = 100;
        newDist[edges[i].second][edges[i].first] = 100;
        floydWarshall(newDist, n);
        if (isReachableWithin100Km(newDist, n)) {
            return true;
        }
    }
    
    return false;
}

int main() {
    int n, m;
    cout << "Введите количество городов и дорог: ";
    cin >> n >> m;

    vector<vector<int>> dist(n, vector<int>(n, INF));
    
    for (int i = 0; i < n; ++i)
        dist[i][i] = 0;
    
    cout << "Введите дороги в формате: город1 город2 расстояние\n";
    for (int i = 0; i < m; ++i) {
        int u, v, d;
        cin >> u >> v >> d;
        --u; --v;
        dist[u][v] = d;
        dist[v][u] = d;
    }

    if (canReachAllCitiesWithin100Km(dist, n)) {
        cout << "Можно сделать все города доступными за 100 км или меньше, добавив до трех дорог.\n";
    } else {
        cout << "Невозможно сделать все города доступными за 100 км или меньше, даже добавив три дороги.\n";
    }

    return 0;
}
