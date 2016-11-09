#ifndef _LIST_H
#define _LIST_H

typedef struct list_node {
	void *data;
	struct list_node *next;
} list_node;

/* linked list */

/**
 * function: list_create
 * 开辟一个节点 返回指向该节点的指针
 * @param  data -->NULL to create a NULL list/node
 * @return      a list
 */
list_node* list_create(void *data);

/**
 * function: list_destroy
 * 完全删除一条链表
 * @param list A pointer to a pointer to a list
 */
void list_destroy(list_node **list);

/**
 * function: list_insert_after
 * 头插法：在头节点后插入新节点
 * @param  node a node to insert after
 * @param  the new nod will contain
 * @return      the new list
 */
list_node* list_insert_after(list_node *node, void *data);

/**
 * function: list_insert_beginning
 * 在头节点前面插入新的节点
 * @param  list 被插入的链表
 * @param  data 要插入的新节点
 * @return      新的链表
 */
list_node* list_insert_beginning(list_node *list, void *data);

/**
 * function: list_insert_end
 * 在链表尾部插入新的节点
 * @param  list 被插入的链表
 * @param  data 要插入的新节点
 * @return      新的链表
 */
list_node* list_insert_end(list_node *list, void *data);

/**
 * function: list_remove
 * 移除指定的节点
 * @param list 被操作的链表
 * @param node 要删除的节点
 */
void list_remove(list_node **list, list_node *node);

/**
 * function: list_remove_by_data
 * 通过比较值，删除对应节点
 * @param list 被操作的链表
 * @param data 要删除节点的数据值
 */
void list_remove_by_data(list_node **list, void *data);

/**
 * function: list_find_node
 * 通过节点指针查找对应的节点
 * @param  list 被操作的链表
 * @param  node 要查找的节点指针
 * @return      返回链表中对应节点
 */
list_node* list_find_node(list_node *list, list_node *node);

/**
 * function: list_find_by_data
 * 通过节点值查找对应的节点
 * @param  list 被操作的链表
 * @param  node 要查找的节点值
 * @return      返回链表中对应节点
 */
list_node* list_find_by_data(list_node *list, void *data);

/**
 * function: list_find
 * 通过回调函数查找对应的节点
 * @param  list   被操作的链表
 * @param  func() 回调函数
 * @param  data   需要查找的数值
 * @return        返回链表中对应节点
 */
list_node* list_find(list_node *list, int(*func)(list_node*,void*), void *data);

#endif
