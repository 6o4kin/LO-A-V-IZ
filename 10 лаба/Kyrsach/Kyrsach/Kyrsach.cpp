#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <clocale> 

#define MAX_VERTICES 10  // Максимальное количество вершин в графе

int main() {
    setlocale(LC_ALL, "Russian");

    int n;  // Количество вершин
    int i, j;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];

    // Инициализация генератора случайных чисел
    srand(time(NULL));

    // Введите количество вершин графа
    printf("Введите количество вершин в графе (не более %d): ", MAX_VERTICES);
    scanf("%d", &n);

    // Генерация матрицы смежности
    printf("Матрица смежности графа:\n");
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            if (i == j) {
                adjacencyMatrix[i][j] = 0;  // Нет петли у вершины
            }
            else {
                int random = rand() % 2;  // Случайное 0 или 1 для определения наличия ребра
                adjacencyMatrix[i][j] = random;
                adjacencyMatrix[j][i] = random;  // Граф неориентированный, поэтому симметричен
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }