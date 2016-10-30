
#include "linkqueue.h"
#include "BFS.h"

int visit[N] = {0};

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
		//while( getchar() != '\n');
		getchar();
		// g->A[i][j] = 1;
		g->A[i][j] = g->A[j][i] = 1;
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

int adj_first(graph_t * g, int v)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		if ( 1 == g->A[v][i])
		{
			return i;
		}
	}

	return -1;
}

int adj_next(graph_t * g, int v, int u)
{
	int i;
	for (i = u + 1; i < N; ++i)
	{
		if ( 1 == g->A[v][i])
		{
			return i;
		}
	}

	return -1;
}

int DFS(graph_t *g, int v)
{
	int u;

	printf("%d ", v);
	visit[v] = 1;

	//printf("   pppppppp ");
	//getchar();

	u = adj_first(g, v);

	while( u >= 0 )
	{

		if ( visit[u] == 0 )
		{
			DFS(g, u);
		}

		u = adj_next(g, v, u);

	}

	return 0;
}

int BFS(graph_t *g, int v)
{
	int u;
	//创建一个队列
	linkqueue_t *lq = linkqueue_create();

	//将根结点入队
	linkqueue_input(lq, v);
	visit[v] = 1;

	//循环出队,
	while(!linkqueue_empty(lq))
	{
		v = linkqueue_output_undel(lq);
		printf("v = %d ", v);

		u = adj_first(g, v);

		while( u >= 0)
		{
			if (visit[u] == 0)
			{
				visit[u] = 1;
				linkqueue_input(lq, u);
			}

			u = adj_next(g, v, u);
		}

	}

	return 0;
}

int main(int argc, char const *argv[])
{
	graph_t *g;
	int j;
	g = graph_create();

	graph_input(g);

	graph_output(g);

	DFS(g, 0);

	putchar(10);

	for (j = 0; j < N; ++j)
	{
		visit[j] = 0;
	}


	BFS(g, 1);
	putchar(10);
	return 0;

}

