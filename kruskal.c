#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX];
int parent[MAX];

int find(int x) {
    if(parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void unionSet(int a, int b) {
    parent[a] = b;
}

int compare(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int n, e;
    scanf("%d %d", &n, &e);

    for(int i=0;i<e;i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    for(int i=0;i<n;i++)
        parent[i] = i;

    qsort(edges, e, sizeof(Edge), compare);

    int cost = 0;

    for(int i=0;i<e;i++) {
        int pu = find(edges[i].u);
        int pv = find(edges[i].v);

        if(pu != pv) {
            printf("%d %d %d\n", edges[i].u, edges[i].v, edges[i].w);
            cost += edges[i].w;
            unionSet(pu, pv);
        }
    }

    printf("Total:%d\n", cost);
    return 0;
}