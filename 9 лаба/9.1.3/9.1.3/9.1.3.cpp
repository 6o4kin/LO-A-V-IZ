﻿#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];

void addEdge(int from, int to) {
	graph[from][to] = 1;
	graph[to][from] = 1; // Учтем симметрию для неориентированного графа
}

void initializeGraph(int vertices) {
	for (int i = 0; i < vertices; ++i) {
		for (int j = 0; j < vertices; ++j) {
			graph[i][j] = 0;
		}
	}
}

void printAdjacencyList(int vertices) {
	printf("Список смежности:\n");
	for (int i = 0; i < vertices; ++i) {
		printf("%d: ", i);
		for (int j = 0; j < vertices; ++j) {
			if (graph[i][j] == 1) {
				printf("%d ", j);
			}
		}
		printf("\n");
	}
}

void bfs(int startVertex, int vertices, int distances[]) {
	bool visited[MAX_VERTICES] = { false };

	// Очередь для BFS
	int queue[MAX_VERTICES];
	int front = 0, rear = 0;

	// Начинаем с начальной вершины
	visited[startVertex] = true;
	queue[rear++] = startVertex;
	distances[startVertex] = 0;

	while (front < rear) {
		int currentVertex = queue[front++];

		for (int i = 0; i < vertices; ++i) {
			if (graph[currentVertex][i] == 1 && !visited[i]) {
				visited[i] = true;
				queue[rear++] = i;
				distances[i] = distances[currentVertex] + 1;
			}
		}
	}
}

int main() {

	setlocale(LC_ALL, "Russian");

	int vertices, edges;

	// Введите количество вершин и рёбер
	printf("Введите количество вершин и рёбер графа: ");
	scanf("%d %d", &vertices, &edges);

	initializeGraph(vertices);

	// Заполнение списка рёбрами автоматически
	for (int i = 0; i < edges; ++i) {
		int from = rand() % vertices;
		int to;
		do {
			to = rand() % vertices;
		} while (from == to);

		addEdge(from, to);
	}

	printAdjacencyList(vertices);

	int startVertex;
	// Введите начальную вершину
	printf("Введите начальную вершину: ");
	scanf("%d", &startVertex);

	int distances[MAX_VERTICES];
	for (int i = 0; i < vertices; ++i) {
		distances[i] = INT_MAX;
	}

	bfs(startVertex, vertices, distances);

	// Выведите расстояния от начальной вершины до всех остальных
	printf("Расстояния от вершины %d до всех остальных (по обходу в шири-ну):\n", startVertex);
	for (int i = 0; i < vertices; ++i) {
		if (distances[i] == INT_MAX) {
			printf("До вершины %d: Недостижима\n", i);
		}
		else {
			printf("До вершины %d: %d\n", i, distances[i]);
		}
	}

	return 0;
}
