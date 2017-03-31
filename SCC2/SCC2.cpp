
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <string.h>
#define SIZE 875714
#define FILENAME "C:\\Users\\n419\\Repos\\Graphs\\SCC.txt"

using namespace std;

struct edge
{
	long head;
	edge* next;
};

edge* g[SIZE + 1];
bool visited[SIZE + 1];
long t[SIZE + 1];
long curr_time = 0;
static long sccs[6];

void insert(long size)
{
	for (int i = 1; i<6; i++)
		if (sccs[i]<size)
		{
			for (int j = 5; j>i; j--)sccs[j] = sccs[j - 1];
			sccs[i] = size;
			break;
		}
}

long DFS(long i, long size)
{
	visited[i] = true;
	size++;
	edge *temp = g[i];
	while (temp != NULL)
	{
		if (!(visited[temp->head])) size = DFS(temp->head, size);
		temp = temp->next;
	}
	t[SIZE - curr_time] = i;
	curr_time++;
	return size;
}

void DFSloop()
{
	long size = 0;
	long times_dfs_done = 0;
	for (long i = SIZE; i>0; i--)
	{
		size = 0;
		if (!visited[i])
		{
			times_dfs_done++;
			size = DFS(i, 0);
		}
		insert(size);
	}
}

int main()
{
	FILE *f = fopen(FILENAME, "r");
	for (int i = 1; i <= SIZE; i++)
	{
		g[i] = NULL;
		visited[i] = false;
	}
	char *a = new char[20];
	while (fgets(a, 20, f))
	{
		long n1, n2;
		n2 = atol(a);
		while (a[0] != ' ') a++;
		n1 = atol(++a);
		edge *newedge = new edge;
		newedge->head = n2;
		newedge->next = g[n1];
		g[n1] = newedge;
		a = new char[20];
	}
	fclose(f);
	DFSloop();
	FILE *fp = fopen("C:\\Users\\n419\\Repos\\Graphs\\Times.Txt", "w");
	for (int k = 1; k <= SIZE; k++)
	{
		a = new char[20];
		sprintf(a, "%lu\n", t[k]);
		fputs(a, fp);
	}
	fclose(fp);
	system("PAUSE");
	return EXIT_SUCCESS;
}

