#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

typedef struct list_s{
	struct list_s *prev, *next;
}List, *Plist;

//#define offsetof(s,m) (size_t)&(((s *)0)->m)

//初始化 h： 头节点指针
#define ListInit(h)			\
	do{						\
		(h)->prev = NULL;	\
		(h)->next = NULL;	\
	}while(0)

//头插法
//h:头节点指针
//l:自定义结构体中List类型成员的指针
#define ListHeadInsert(h,l)		\
	do{							\
		(l)->prev = h;			\
		(l)->next = h->next;	\
		(h)->next = l;			\
	}while(0)

//尾插法
////h:头节点指针
//l:自定义结构体中List类型成员的指针
#define ListTailInsert(h,l)			\
	do{								\
		Plist t = h;				\
		while(t->next) t = t->next;	\
		(l)->prev = (t);			\
		(l)->next = (t)->next;		\
		(t)->next = (l);			\
	}while(0)


//查找
//l:要读取的节点的list成员的指针
//struct_type:自定义结构体的类型名
//struct_field: List 类型成员的成员名称(变量名)
#define ListGetData(l, struct_type, struct_field)							\
	( (struct_type *)((char *)(l) - offsetof(struct_type, struct_field)) )	\


//要删除节点的list的指针
//
#define ListDelete(l)							\
	do{											\
		if ((l)->next == NULL)					\
		{										\
			(l)->prev->next= (l)->next;			\
			(l)->prev = NULL;					\
		}										\
		else									\
		{                   			 		\
	        (l)->prev->next = (l)->next;        \
	        (l)->next->prev = (l)->prev;		\
        }       								\
	}while(0)

#endif
