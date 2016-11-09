#include <stdio.h>
#include "list.h"


typedef struct{
    int a;
    List list;
}TEST,*pTEST;


int main(int argc, char** argv)
{
    /*
    TEST t = {1234,{NULL, NULL}};
    Plist l = &t.list;
    //int n = &((TEST)0).list;
    &((pTEST)0)->list;
    printf("%d\n", &((pTEST)0)->list);
    //printf("%d", ((pTEST)((char*)l - (char*)&((pTEST)0)->list))->a);
    printf("%d", ((pTEST)((char*)l - offsetof(TEST,list)))->a);
    */
    TEST test1 = {1234,{NULL, NULL}};
    TEST test2 = {2234,{NULL, NULL}};
    TEST test3 = {3234,{NULL, NULL}};

    List head;
    ListInit(&head);
    ListTailInsert(&head,&test1.list);
    ListTailInsert(&head,&test2.list);
    ListTailInsert(&head,&test3.list);

    List* temp = head.next;
    for(temp = head.next; temp != NULL; temp = temp->next)
    {
        pTEST data_addr = ListGetData(temp,TEST,list);
        printf("%d\n", data_addr->a);
    }

    //printf("%p, %p \n", test2.list.prev, test2.list.next);
    ListDelete(&test3.list);
    for(temp = head.next; temp != NULL; temp = temp->next)
    {
        pTEST data_addr = ListGetData(temp,TEST,list);
        printf("%d\n", data_addr->a);
    }

    return 0;
}
