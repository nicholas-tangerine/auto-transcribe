#ifndef DYNAMIC_LIST_H_
#define DYNAMIC_LIST_H_

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    float *arr;
    uint32_t capacity;
    uint32_t elem_count;
} float_list;

float_list *float_list_init();

void float_list_append(float_list *list, float val);

void *float_list_free(float_list *list);

#endif // DYNAMIC_LIST_H_
