#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

#ifndef DEBUG
#define DEBUG 0
#endif

int al_init(arraylist_t *L, size_t length)
{
    L->data = malloc(sizeof(int) * length);
    if (!L->data) return 1;

    L->length = length;
    L->used   = 0;

    return 0;
}

void al_destroy(arraylist_t *L)
{
    free(L->data);
}


int al_append(arraylist_t *L, int item)
{
    if (L->used == L->length) {
	size_t size = L->length * 2;
	int *p = realloc(L->data, sizeof(int) * size);
	if (!p) return 1;

	L->data = p;
	L->length = size;

	if (DEBUG) printf("Increased size to %lu\n", size);
    }

    L->data[L->used] = item;
    ++L->used;

    return 0;
}


int al_remove(arraylist_t *L, int *item)
{
    if (L->used == 0) return 1;

    --L->used;

    if (item) *item = L->data[L->used];

    return 0;
}

int al_insert(arraylist_t *list, int index, int item)
{
    if(index<0)
    {
        return 1;
    }
    if(list->length<=index)
    {
        int new_length = (list->length)*2;
        if ((list->length)*2<index+1)
        {
            new_length=index+1;
        }
        list->length=new_length;
        list->data=realloc(list->data, sizeof(int)*new_length);
        if(!list->data)
        {
            return 1;
        }
        list->used=index+1;
    }
    else
    {
        if(list->used<=index)
        {
            //list->data=realloc(list->data, sizeof(int)*(index+1));
            list->used = index+1;
        }
        else
        {
            if(list->length==list->used)
            {
                list->length=list->length*2;
                list->data=realloc(list->data, sizeof(int)*list->length);
            }
            list->used++;
            for(int i=list->used-1; i>index; i--)
            {
                list->data[i]=list->data[i-1];
            }
        }
    }

    list->data[index]=item;
    return 0;
}