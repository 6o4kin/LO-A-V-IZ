#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>
int main()
{
	FILE* fp;
	int s = -1, minchislo, min, SIZE = 0, menu = 0;
	int** a; // матрица связей
	int* d; // минимальное расстояние
	int* v; // посещенные вершины
	int begin_index = 0;
	char namefile[20];
	char keyboard;
	system("chcp 1251");
	system("cls");
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf("Введите название файла (до 20 символов): ");
	gets_s(namefile);
	fp = fopen(namefile, "w");
	// меню
	printf("Введите количество вершин: ");
	while (SIZE <= 0) {
		scanf_s("%d", &SIZE);
		if (SIZE <= 0) {
			printf("Введено неверное значение\n");
			printf("Введите количество вершин: ");
		}
	}
	a = (int**)malloc(SIZE * sizeof(int*));
	for (int i = 0; i < SIZE; i++) a[i] = (int*)malloc(SIZE * sizeof(int));
	while (menu == 0) {
		printf("\nНажмите клавишу для выбора действия\n1.Рандомное заполнение\n2.Заполнение вручную\n3.Выход\n");
		keyboard = _getch();
		if (keyboard == 49) {
			for (int i = 0; i < SIZE; i++)
			{
				a[i][i] = 0;
				for (int j = i + 1; j < SIZE; j++) {
					a[i][j] = rand() % 20;
					a[j][i] = a[i][j];
				}
			}
			menu = 1;
		}
		if (keyboard == 50) {
			for (int i = 0; i < SIZE; i++) {
				a[i][i] = 0;
				for (int j = i + 1; j < SIZE; j++) {
					printf("\nВведите расстояние %d - %d: ", i + 1, j + 1);
					scanf_s("%d", &s);
					if (s < 0) {
						while (s < 0) {
							printf("Введено неверное значение");
							printf("\nВведите расстояние %d - %d: ", i + 1, j + 1);
							scanf_s("%d", &s);
						}
					}
					a[i][j] = s;
					a[j][i] = s;
				}
			}
			menu = 1;
		}
		if (keyboard == 51) exit(0);
	}
	// Вывод матрицы связей
	printf("Ваша матрица:\n");
	fprintf(fp, "Ваша матрица:\n");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++) {
			printf("%5d ", a[i][j]);
			fprintf(fp, "%5d ", a[i][j]);
		}
		printf("\n");
		fprintf(fp, "\n");
	}
	//Инициализация вершин и расстояний
	v = (int*)malloc(SIZE * sizeof(int));
	d = (int*)malloc(SIZE * sizeof(int));
	for (int i = 0; i < SIZE; i++)
	{
		d[i] = 100000;
		v[i] = 1;
	}
	d[begin_index] = 0;
	// Шаг алгоритма
	do {
		minchislo = 100000;
		min = 100000;
		for (int i = 0; i < SIZE; i++)
		{ // Если вершину ещё не обошли и вес меньше min
			if ((v[i] == 1) && (d[i] < min))
			{ // Переприсваиваем значения
				min = d[i];
				minchislo = i;
			}
		}
		// Добавляем найденный минимальный вес
		// к текущему весу вершины
		// и сравниваем с текущим минимальным весом вершины
		if (minchislo != 100000)
		{
			for (int i = 0; i < SIZE; i++)
			{
				if (a[minchislo][i] > 0)
				{
					s = min + a[minchislo][i];
					if (s < d[i])
					{
						d[i] = s;
					}
				}
			}
			v[minchislo] = 0;
		}
	} while (minchislo < 100000);
	// Вывод кратчайших расстояний до вершин
	printf("\nКратчайшие расстояния до вершин: \n");
	fprintf(fp, "\nКратчайшие расстояния до вершин: \n");
	for (int i = 0; i < SIZE; i++) {
		printf("%5d ", d[i]);
		fprintf(fp, "%5d ", d[i]);
	}
	// Восстановление пути
	int* ver; // массив посещенных вершин
	int end = SIZE - 1; // индекс конечной вершины
	ver = (int*)malloc(SIZE * sizeof(int));
	ver[0] = end + 1; // начальный элемент - конечная вершина
	int k = 1; // индекс предыдущей вершины
	int weight = d[end]; // вес конечной вершины
	while (end != begin_index) // пока не дошли до начальной вершины
	{
		for (int i = 0; i < SIZE; i++) // просматриваем все вершины
			if (a[i][end] != 0) // если связь есть
			{
				int s = weight - a[i][end]; // определяем вес пути из предыдущей вершины
				if (s == d[i]) // если вес совпал с рассчитанным
				{ // значит из этой вершины и был переход
					weight = s; // сохраняем новый вес
					end = i; // сохраняем предыдущую вершину
					ver[k] = i + 1; // и записываем ее в массив
					k++;
				}
			}
	}
	// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
	printf("\nВывод кратчайшего пути\n");
	fprintf(fp, "\nВывод кратчайшего пути\n");
	for (int i = k - 1; i >= 0; i--) {
		printf("%3d ", ver[i]);
		fprintf(fp, "%3d ", ver[i]);
	}
	fclose(fp);
	free(a);
	free(v);
	free(d);
	free(ver);
	return 0;
}
