#include <stdio.h>
#include <stdlib.h>

#define N 5

typedef int vtype_t;
typedef int adjtype_t;

typedef struct graph
{
	vtype_t V[N];
	adjtype_t A[N][N];
}graph_t;

graph_t * graph_create(){
	graph_t *g = (graph_t *)malloc(sizeof(graph_t));

	int i = 0;

	for (i = 0; i < N; ++i)
	{
		g->V[i] = i;
	}
	return g;
}

int graph_input(graph_t * g)
{
	int i,j;
	while(scanf("%d %d", &i, &j) == 2)
	{
		getchar();
		g->A[i][j] = i+1;
		//g->A[i][j] = g->A[j][i] = i+1;
	}

	return 0;
}

int graph_output(graph_t * g)
{
	int i,j;
	printf("   V0 V1 V2 V3 V4 	\n");
	for (i = 0; i < N; ++i)
	{
		printf("V%d ", i);
		for (j = 0; j < N; ++j)
		{
			printf(" %d ", g->A[i][j]);
		}

		putchar(10);
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	graph_t *g;
	g = graph_create();

	graph_input(g);

	graph_output(g);

	return 0;

}