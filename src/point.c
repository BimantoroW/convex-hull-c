#include <stdlib.h>
#include "point.h"

#define EPSILON 0.000001f

int point_equal(point_t a, point_t b) {
    return abs(a.x - b.x) < EPSILON && abs(a.y - b.y) < EPSILON;
}

int point_ccw(point_t a, point_t b, point_t c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x) > 0;
}

point_t *point_rand(int n, int max_x, int max_y) {
    point_t *points = calloc(n, sizeof(point_t));
    for (int i = 0; i < n; i++) {
        float x = ((float)rand() / (float)RAND_MAX) * max_x;
        float y = ((float)rand() / (float)RAND_MAX) * max_y;
        points[i] = (point_t){x, y};
    }
    return points;
}

point_stack_t *point_stack(void) {
    point_stack_t *stack = malloc(sizeof(point_stack_t));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void point_stack_push(point_stack_t *stack, point_t point) {
    point_node_t *new = malloc(sizeof(point_node_t));
    new->coords = point;
    new->next = stack->top;
    stack->top = new;
    stack->size++;
}

point_t point_stack_pop(point_stack_t *stack) {
    point_node_t *tmp = stack->top;
    point_t data = stack->top->coords;
    stack->top = stack->top->next;
    stack->size--;
    free(tmp);
    return data;
}

void point_stack_free(point_stack_t *stack) {
    point_node_t *cur = stack->top;
    while (cur != NULL) {
        point_node_t *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(stack);
}

point_t *point_stack_to_arr(point_stack_t *stack) {
    int n = stack->size;
    point_t *arr = calloc(n, sizeof(point_t));
    point_node_t *cur = stack->top;
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = cur->coords;
        cur = cur->next;
    }
    return arr;
}

void merge(point_t *arr, int p, int q, int r) {
    int nL = q - p + 1;
    int nR = r - q;

    point_t *L = calloc(nL, sizeof(point_t));
    point_t *R = calloc(nR, sizeof(point_t));
    for (int i = 0; i < nL; i++) {
        L[i] = arr[p + i];
    }
    for (int j = 0; j < nR; j++) {
        R[j] = arr[q + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = p;

    while (i < nL && j < nR) {
        if (L[i].x - R[j].x < -EPSILON) {
            arr[k] = L[i];
            i++;
        } else if (L[i].x - R[j].x > EPSILON) {
            arr[k] = R[j];
            j++;
        } else {
            if (L[i].y - R[i].y < -EPSILON) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
        }
        k++;
    }

    while (i < nL) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < nR) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(R);
    free(L);
}

void point_sort_by_x(point_t *arr, int p, int r) {
    if (p >= r) {
        return;
    }
    int q = (p + r) / 2;
    point_sort_by_x(arr, p, q);
    point_sort_by_x(arr, q + 1, r);
    merge(arr, p, q, r);
}