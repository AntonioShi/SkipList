#include <iostream>
#include "SkipList.h"
/*
 * skipList是一种随机化的数据结构，基于并联的链表，实现简单，插入，删除，查找的复杂均为O（logN）
 * 本质是空间换时间，但在当今硬件发达的情况下，很主流
 * 红黑树等这样的平衡数据结构查找的时间复杂读也为O（logN），但skipList更加简单易行
 */
int main()
{
    skip_list *sl=create_sl();
    printf("asdasd\n") ;
    int i=1;
    for(;i<11111; ++i)
    {
        insert(sl, i, i);
    }
    for(i=11; i<11111; ++i)
    {
        if(!erase(sl, i))
            printf("No!\n");
    }
    print_sl(sl);
    int *p=search(sl, 10);
    if(p)
        printf("value of key 10 is %d\n", *p);
    sl_free(sl);
    return 0;
}
