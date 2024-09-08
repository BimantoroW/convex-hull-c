#ifndef EDGE_H
#define EDGE_H

#include "point.h"

typedef struct edge {
    point_t src, dst;
    struct edge *next;
} edge_t;

typedef struct edge_list {
    edge_t *head;
    int size;
} edge_list_t;

edge_list_t *edge_list(void);
void edge_list_add(edge_list_t *edges, point_t src, point_t dst);
point_t edge_list_remove(edge_list_t *edges, point_t src);
void edge_list_free(edge_list_t *edges);

#endif