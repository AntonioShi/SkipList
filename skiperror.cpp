
 //Created by antonio on 17-11-28.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int keyType ;
typedef int valueType ;
#define MAX_L 16 //最大层数
#define new_node(n)((Node *)malloc(sizeof(Node) + n*sizeof(Node *)))

typedef struct node{
    keyType key ;
    valueType value ;
    struct node *next[1] ;//后继指针数组，柔性数组，可实现结构体变长
}Node;

typedef struct skip_list{
    int level;//层数
    Node *head ;//指向头结点
}skip_list;


//跳表结点的创建
Node* Create_node(int level, keyType key, valueType value){
    Node *p = new_node(level) ;
    if (!p)
        return NULL ;
    p->key = key ;
    p->value = value ;
    return p ;
}

//跳表的创建
skip_list* Create_sl(){
    skip_list *sl = (skip_list *)malloc(sizeof(skip_list)) ;//申请跳表储存空间
    if (sl == NULL)
        return NULL ;

    sl->level = 0 ;
    Node *h = Create_node(MAX_L-1, 0, 0) ;//创建头结点
    if (h == NULL){
        free(sl) ;
        return NULL ;
    }
    sl->head = h ;
    for (int i = 0; i < MAX_L; ++i) {
        h->next[i] = NULL ;
    }
    srand(time(0)) ;
    return sl ;
}

//跳表插入:完全随机，插入元素的层数都是随机
/*
 * 1.查找到待插入位置，每层更新数组
 * 2.需要一个随机产生层数
 * 3.从高层到底层插入，与普通链表的插入完全相同
 */
int RandomLevel(){//相当于丢硬币，正面（奇数）继续丢，直到反面停止，level作为层数
    int level = 1 ;
    while (rand() % 2)
        level++ ;
    level = MAX_L > level ? level:MAX_L ;
    return level ;
}

bool Insert(skip_list *sl, keyType key, valueType value){
    Node *update[MAX_L] ;
    Node *q = NULL, *p = sl->head ;//初始化
    int i = sl->level - 1 ;

    /***********step1*****************/
    //从最高层往下查找需要插入的位置，并更新update
    //即把降层结点指针保存到update数组
    for (; i >= 0; --i){
        while ((q = p->next[i]) && q->key < key)
            p = q ;
        update[i] = p ;
    }
    if (q && q->key == key){//如果key已经存在的情况下
        q->value = value ;
        return true ;
    }

    /***********step2*****************/
    //产生一个随机层数
    int level = RandomLevel() ;
    //如果随机产生的层数比跳表目前的层数大
    if (level > sl->level){
        //在update数组中新添加的层指向head
        for (i = sl->level; i < level; ++i){
            update[i] = sl->head ;
        }
        sl->level = level ;
    }

    /***********step3*****************/
    //新建一个待插入结点， 一层一层插入
    q = Create_node(level, key, value) ;
    if (!q)
        return false ;

    //逐层更新结点的指针，和普通链表一样的插入
    for (i = level-1; i >= 0; --i){
        q->next[i] = update[i]->next[i] ;//分清 update[] next[]的意义
        update[i]->next[i] = q ;
    }
    return true ;
}


//跳表删除
//需要每层找到需要删除的位置，其余的删除操作和普通链表的删除一样，但要记得更新update数组
bool Erase(skip_list *sl, keyType key){
    Node *update[MAX_L] ;
    Node *q = NULL, *p = sl->head ;
    int i = sl->level-1 ;//*
    for (; i >= 0; --i){
        while ((q = p->next[i]) && q->key < key){
            p = q ;
        }
        update[i] = p ;
    }
    //判断是否为待删除的key
    if (!q || (q && q->key != key))
        return false ;
    //逐层删除
    for (i = sl->level-1; i >= 0; --i){//*
        if (update[i]->next[i] = q){
            update[i]->next[i] = q->next[i] ;
            //如果删除的是最高层的结点，则level--
            if (sl->head->next[i] == NULL)
                sl->level-- ;
        }
    }

    free(q) ;
    q = NULL ;
    return true ;
}

//跳表查找
//跳表的优点在于查找比普通链表块
valueType *Search(skip_list *sl, keyType key){
    Node *q, *p = sl->head ;
    q = NULL ;
    int i = sl->level - 1 ;
    for (; i >= 0; --i){
        while ((q = p->next[i]) && q->key < key){
            p = q ;
        }
        if (q && key == q->key)
            return &(q->value) ;
    }
    return NULL ;
}

//print
void Print_sl(skip_list *sl){
    Node *q;
    int i = sl->level-1 ;
    for (; i >= 0; --i){
        q = sl->head->next[i] ;
        printf("level %d\n", i+1) ;
        while (q){
            printf("key: %d val: %d\t", q->key, q->value) ;
            q = q->next[i] ;
        }
        printf("\n") ;
    }
}
//跳表销毁
void Free_sl(skip_list *sl){
    if (!sl)
        return;
    Node *q = sl->head ;
    Node *next ;

    while (q){
        next = q->next[0] ;
        free(q) ;
        q = next ;
    }
    free(sl) ;
}



// Created by antonio on 17-11-28.



