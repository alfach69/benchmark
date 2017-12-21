#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include<cstdlib>
#include<ctime>

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
void print_matrix();
void scan_matrix();
int test_matrix_0();
void print_solutions(int r);

int main() {
	//int start = clock();
	srand(time(NULL));
	int i, rang;
	int count = 0;
	//scanf("%d %d", &m, &n);
	m = 500;
	n = 200;
	a = (float**)malloc(sizeof(pFloat)*m);
	J = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		J[i] = -1;
	for (i = 0; i < m; i++)
		a[i] = (float*)malloc(sizeof(float)*(n + 1));
	for (;;)
	{
		int start = clock();
		scan_matrix();
		//print_matrix();
		rang = gauss_right();
		gauss_back(rang);
		/*if(rang == 0 && test_0_column(n, 0) == 0)
		printf("R - all real numbers\n");
		else
		if(test_matrix_0() == 0)
		printf("No solutions\n");
		else*/
		int finish = clock();
		printf("%d", ++count);
		printf(" ");
		printf("%d\n", finish - start);
	}

	//int finish = clock();
	//printf("%d\n", finish - start);

	for (i = 0; i < m; i++)
		free(a);
	free(a);
	free(J);
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

void print_matrix() {
	int i, j;
	for (i = 0; i < m; i++)
	{
		printf("||\t%f\t", a[i][0]);
		for (j = 1; j < n; j++)
			printf("%f\t", a[i][j]);
		printf("|  %f\t||\n", a[i][n]);
	}
}

void scan_matrix() {
	int i, j;
	//srand(time(NULL));
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			//scanf("%f", &a[i][j]);
			a[i][j] = rand() % 1000;
			//a[i][n] = rand() % 1000 * 2000;
		}
	}
}

int test_matrix_0() {
	int i, j, count = 0;
	for (i = 0; i < m; i++)
	{
		count = 0;
		for (j = 0; j < n; j++)
			if (a[i][j] != 0) count++;
		if (count == 0 && a[i][n] != 0) return 0;
	}
	return 1;
}

void print_solutions(int r) {
	int i, j, k = 0, d;
	pFloat* b = (float**)malloc(sizeof(pFloat)*n);
	for (j = 0; j < n; j++)
		b[j] = (float*)malloc(sizeof(float)*(n - r + 1));
	/* make supporting matrix*/
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
		printf(" x%d = ", i + 1);
		for (j = 0; j < n - r; j++)
		{
			if (b[i][j] > 0)
				printf(" + %f * t%d", b[i][j], j + 1);
			if (b[i][j] < 0)
				printf(" - %f * t%d", -b[i][j], j + 1);
		}
		if (b[i][n - r] >= 0)
			printf(" + %f\n", b[i][n - r]);
		if (b[i][n - r] < 0)
			printf(" - %f\n", -b[i][n - r]);
	}
	for (i = 0; i < n; i++)
		free(b);
	free(b);
}
