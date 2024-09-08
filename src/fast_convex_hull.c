#include <stdlib.h>
#include <stdio.h>
#include "point.h"

int last_three_points_clockwise(point_stack_t *stack) {
    point_node_t *first = stack->top;
    point_node_t *second = first->next;
    point_node_t *third = second->next;
    return !point_ccw(first->coords, second->coords, third->coords);
}

void remove_middle(point_stack_t *stack) {
    point_t top = point_stack_pop(stack);
    point_stack_pop(stack);
    point_stack_push(stack, top);
}

// upper will become freed and thus shouldn't be used after this call
void merge_stacks(point_stack_t *upper, point_stack_t *lower) {
    point_node_t *lower_last = lower->top;
    while (lower_last->next != NULL) {
        lower_last = lower_last->next;
    }
    point_stack_pop(upper);
    lower_last->next = upper->top;
    lower->size += upper->size;
    free(upper);
}

point_t *fast_convex_hull(point_t *points, int n, int *n_ch) {
    point_sort_by_x(points, 0, n - 1);

    point_stack_t *upper_stack = point_stack();
    point_stack_push(upper_stack, points[0]);
    point_stack_push(upper_stack, points[1]);
    for (int i = 2; i < n; i++) {
        point_stack_push(upper_stack, points[i]);
        while (upper_stack->size > 2 && !last_three_points_clockwise(upper_stack)) {
            remove_middle(upper_stack);
        }
    }

    point_stack_t *lower_stack = point_stack();
    point_stack_push(lower_stack, points[n - 1]);
    point_stack_push(lower_stack, points[n - 2]);
    for (int i = n - 3; i >= 0; i--) {
        point_stack_push(lower_stack, points[i]);
        while (lower_stack->size > 2 && !last_three_points_clockwise(lower_stack)) {
            remove_middle(lower_stack);
        }

    }

    merge_stacks(upper_stack, lower_stack);
    point_t *ch = point_stack_to_arr(lower_stack);
    *n_ch = lower_stack->size;
    point_stack_free(lower_stack);
    return ch;
}