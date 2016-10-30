#ifndef _BFS_H_
#define _BFS_H_


#include <stdio.h>
#include <stdlib.h>

#define N 9

typedef int vtype_t;
typedef int adjtype_t;

typedef struct graph
{
	vtype_t V[N];
	adjtype_t A[N][N];
}graph_t;


#endif