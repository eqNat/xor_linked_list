#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "XORLL.h"

List::List()
{
    this->hanger = (Node*)calloc(sizeof(struct List), 1);
    this->current = this->hanger;
    this->previous = (uintptr_t) this->current;
}

#define SWAP(a, b) a ^= b, b ^= a, a ^= b

void moveLeft(struct List *list)
{
    SWAP(list->previous, list->current_int);
    list->previous ^= list->current->PxorN;
}

void moveRight(struct List *list)
{
    list->previous ^= list->current->PxorN;
    SWAP(list->previous, list->current_int);
}

void reverse(struct List *list)
{
    list->previous ^= list->current->PxorN;
}

void insert(struct List *list, uint64_t data)
{
    list->hanger->data = data;

    list->hanger->PxorN = list->previous ^ list->current_int;
    list->current->PxorN ^= list->previous ^ list->hanger_int;
    SWAP(list->previous, list->hanger_int);
    list->hanger->PxorN ^= list->current_int ^ list->previous;

    list->hanger = (Node*)calloc(sizeof(struct Node), 1);
}

int main()
{
    struct List list;
    // Allocate ahead of time
    list.hanger = (Node*)calloc(sizeof(struct List), 1);
    list.current = list.hanger;
    list.previous = (uintptr_t) list.current;

    insert(&list, 30);
    insert(&list, 35);
    insert(&list, 40);
    insert(&list, 45);
    insert(&list, 50);

    printf("printing list 3 times...\n");
    for (int i = 0; i < 15; i++) {
        printf("%lu\n", list.current->data);
        moveRight(&list);
    }
}
