#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "edge.h"

edge_list_t *edge_list(void) {
    edge_list_t *edges = malloc(sizeof(edge_list_t));
    edges->head = NULL;
    edges->size = 0;
    return edges;
}

void edge_list_add(edge_list_t *edges, point_t src, point_t dst) {
    edge_t *new = malloc(sizeof(edge_t));
    new->src = src;
    new->dst = dst;
    new->next = edges->head;
    edges->head = new;
    edges->size++;
}

point_t edge_list_remove(edge_list_t *edges, point_t src) {
    if (point_equal(edges->head->src, src)) {
        point_t dst = edges->head->dst;
        edge_t *tmp = edges->head;
        edges->head = edges->head->next;
        edges->size--;
        free(tmp);
        return dst;
    }
    for (edge_t *cur = edges->head, *prev = NULL; cur != NULL; cur = cur->next) {
        if (point_equal(cur->src, src)) {
            point_t dst = cur->dst;
            edge_t *tmp = edges->head;
            prev->next = cur->next;
            edges->size--;
            free(tmp);
            return dst;
        }
        prev = cur;
    }
    perror("get_and_remove");
    exit(EXIT_FAILURE);
}

void edge_list_free(edge_list_t *edges) {
    edge_t *cur = edges->head;
    while (cur != NULL) {
        edge_t *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(edges);
}