#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "convex_hull.h"
#include "point.h"
#include "edge.h"

point_t *sort_clockwise(edge_list_t *edges) {
    point_t *sorted = calloc(edges->size + 1, sizeof(point_t));

    point_t first_src = edges->head->src;
    sorted[0] = first_src;
    int i = 1;
    while (edges->size > 0) {
        point_t dst = edge_list_remove(edges, sorted[i - 1]);
        sorted[i] = dst;
        i++;
    }

    return sorted;
}

point_t *convex_hull(point_t *points, int n, int *n_ch) {
    point_t *ch = NULL;
    edge_list_t *edges = edge_list();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            point_t p = points[i];
            point_t q = points[j];
            if (!point_equal(p, q)) {
                int valid = 1;
                for (int k = 0; k < n; k++) {
                    point_t r = points[k];
                    if (!point_equal(r, p) || !point_equal(r, q)) {
                        if (point_ccw(p, q, r)) {
                            valid = 0;
                            break;
                        }
                    }
                }
                if (valid) {
                    edge_list_add(edges, p, q);
                }
            }
        }
    }
    *n_ch = edges->size + 1;
    ch = sort_clockwise(edges);
    edge_list_free(edges);
    return ch;
}