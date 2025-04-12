#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct {
    int v;
    int *vis;
    NODE **alst;
} GPH;

typedef struct {
    int top;
    int capacity;
    int *arr;
} STK;

// === UTILS ===

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));
    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

STK *create_stack(int capacity) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(capacity * sizeof(int));
    s->top = -1;
    s->capacity = capacity;
    return s;
}

void push(STK *s, int val) {
    s->arr[++(s->top)] = val;
}

void wipe(GPH *g) {
    for (int i = 0; i < g->v; i++) {
        g->vis[i] = 0;
    }
}

void DFS(GPH *g, int start) {
    g->vis[start] = 1;
    NODE *adj = g->alst[start];
    while (adj) {
        if (!g->vis[adj->data]) {
            DFS(g, adj->data);
        }
        adj = adj->next;
    }
}

void insert_edges(GPH *g, int edg_nr) {
    int src, dest;
    printf("Adauga %d muchii (noduri numerotate de la 0 la %d):\n", edg_nr, g->v - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

// === LOGICA DE VERIFICARE ===

int exista_drum(GPH *g, int a, int b) {
    wipe(g);
    DFS(g, a);
    return g->vis[b];
}

// === MAIN ===

int main() {
    int nrv, edg_nr, a, b;

    printf("Cate restaurante (noduri) sunt? ");
    scanf("%d", &nrv);

    GPH *g = create_g(nrv);

    printf("Cate drumuri (muchii)? ");
    scanf("%d", &edg_nr);

    insert_edges(g, edg_nr);

    printf("Verificam daca exista drum intre care doua restaurante?\n");
    scanf("%d %d", &a, &b);

    if (exista_drum(g, a, b)) {
        printf("EXISTA drum intre %d si %d\n", a, b);
    } else {
        printf("NU EXISTA drum intre %d si %d\n", a, b);
    }

    return 0;
}
