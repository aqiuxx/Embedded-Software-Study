#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_

#include <stdio.h>
#include <stdlib.h>

#define N 32

//定义数据类型
typedef int datatype_t;

//定义结构体
typedef struct {
	datatype_t data[N];
	int top;
}seqstack_t;

extern seqstack_t *seqstack_create();
extern int seqstack_full(seqstack_t *s);
extern int seqstack_empty(seqstack_t *s);
extern int seqstack_push(seqstack_t *s, datatype_t value);
extern int seqstack_show(seqstack_t *s);
extern datatype_t seqstack_pop(seqstack_t *s);

#endif
