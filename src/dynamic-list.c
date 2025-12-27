#include "dynamic-list.h"

const uint32_t INITIAL_SIZE = 1024;
const uint32_t GROWTH_FACTOR = 2;


float_list *float_list_init() {
    float_list *out = malloc(1, sizeof(float_list));

    float_list->arr = malloc(INITIAL_SIZE * sizeof(float));
    float_list->capacity = INITIAL_SIZE;
    float_list->elem_count = 0;

    return out;
}

void float_list_append(float_list *list, float val) {
    if (list->elem_count == list->capacity) {
        float_list *new = calloc(list->capacity * GROWTH_FACTOR, sizeof(float));
        memcpy(new, list->arr, list->capacity);
        free(list->arr);
        list->arr = new;
    }

    list[elem_count] = val;
    elem_count++;

    return;
}

void *float_list_free(float_list *list) {
    free(list->arr);
    free(list);

    return;
}
