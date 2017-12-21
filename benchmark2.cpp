#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <locale>

typedef float* pFloat;

pFloat *a;
int *J;
int m, n;
int gauss_right();
void gauss_back(int r);
int test_0_column(int j, int m1);
void revers_strings(int i1, int i2);
void comp_string(int i, float l);
void sum_strings(int i1, int i2, float l);
void scan_matrix();
void solution(int r);

int main() {
	setlocale(LC_ALL, "Russian");
	printf("Бенчмарк, основанный на решении СЛАУ методом Гаусса\n");
	printf("=======================================================================================================================\n");
	printf("Введите количество уравнений и переменных в СЛАУ: ");
	scanf_s("%d", &m);
	//int start = clock();
	srand(time(NULL));
	int i, rang;
	int otime = 0;
	float power;
	n = m;
	//m = 500; //кол-во уравнений
	//n = 200; //кол-во неизвестных
	a = (float**)malloc(sizeof(pFloat)*m);
	J = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		J[i] = -1;
	for (i = 0; i < m; i++)
		a[i] = (float*)malloc(sizeof(float)*(n + 1));
	for (long long int nomer = 1;;++nomer)
	{
		
		scan_matrix();
		int start = clock();
		rang = gauss_right(); //прямой ход
		gauss_back(rang); //обратный ход
		solution(rang); //окончательное решение
		int finish = clock();
		otime += (finish - start);
		
		printf("\r");
		printf("Времени прошло: %d ", otime / 1000);
		printf("(c)\t");
		printf("№ СЛАУ: %d\t", nomer);
		if ((finish - start) < 1000)
		{
			printf("Время решения СЛАУ: %d ", finish - start);
			printf("(мс)\t");
		}
		else if ((finish - start) >= 1000)
		{
			float timework = (float)(finish - start) / 1000;
			printf("Время решения СЛАУ: %0.3f ", timework);
			printf("(с)\t");
		}
		power = 60000 / (float)(otime / nomer);
		
		printf("Производительность: %0.3f ", power);
		printf("СЛАУ в минуту");


	}

	return 0;
}

int gauss_right() {
	int k, j, i;
	for (k = 0; k < n, k < m; k++)
	{
		for (j = k; j < n; j++)
			if (test_0_column(j, k)) break;
		if (j == n) break;
		for (i = k; i < m; i++)
			if (a[i][j] != 0)
			{
				revers_strings(i, k);
				break;
			}
		J[k] = j;
		comp_string(k, 1 / a[k][j]);
		for (i = k + 1; i < m; i++)
			sum_strings(i, k, -a[i][j]);
	}
	return k;
}

void gauss_back(int r) {
	int k, j, i;
	for (k = r - 1; k >= 0; k--)
	{
		comp_string(k, 1 / a[k][J[k]]);
		for (i = k - 1; i >= 0; i--)
			sum_strings(i, k, -a[i][J[k]]);
	}
}

int test_0_column(int j, int m1) {
	int i, count = 0;
	for (i = m1; i < m; i++)
		if (a[i][j] != 0)  count++;
	return count;
}

void revers_strings(int i1, int i2) {
	int j;
	float b;
	for (j = 0; j <= n; j++)
	{
		b = a[i1][j];
		a[i1][j] = a[i2][j];
		a[i2][j] = b;
	}
}

void comp_string(int i, float l) {
	int j;
	for (j = 0; j <= n; j++)
		a[i][j] *= l;
}

void sum_strings(int i1, int i2, float l) {
	int j;
	for (j = 0; j <= n; j++)
		a[i1][j] += a[i2][j] * l;
}

void scan_matrix() {
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			a[i][j] = rand();
		}
	}
}

void solution(int r) {
	int i, j, k = 0, d;
	pFloat* b = (float**)malloc(sizeof(pFloat)*n);
	for (j = 0; j < n; j++)
		b[j] = (float*)malloc(sizeof(float)*(n - r + 1));
	for (i = 0; i < n; i++)
		if (i == J[k])
		{
			d = 0;
			for (j = 0; j < n; j++)
				if (j != J[d])
					b[i][j - d] = -a[i][j];
				else
					d++;
			b[i][n - r] = a[k][n];
			k++;
		}
		else
		{
			for (j = 0; j < n; j++)
				b[i][j] = 0;
			b[i][n - r] = 0;
			b[i][i - k] = 1;
		}
	for (i = 0; i < n; i++)
	{ 
		free(b[i]);
	}
	free(b);
}
