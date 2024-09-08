#ifndef POINT_H
#define POINT_H

typedef struct point {
    float x, y;
} point_t;

typedef struct point_node {
    point_t coords;
    struct point_node *next;
} point_node_t;

typedef struct point_stack {
    point_node_t *top;
    int size;
} point_stack_t;

int point_equal(point_t a, point_t b);
int point_ccw(point_t a, point_t b, point_t c);
point_t *point_rand(int n, int max_x, int max_y);
point_stack_t *point_stack(void);
void point_stack_push(point_stack_t *stack, point_t point);
point_t point_stack_pop(point_stack_t *stack);
void point_stack_free(point_stack_t *stack);
point_t *point_stack_to_arr(point_stack_t *stack);
void point_sort_by_x(point_t *points, int p, int q);

#endif