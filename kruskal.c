#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Edge structure
typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX];
char locations[MAX][50];
int parent[MAX];

// Performance counters
int findCount = 0;
int unionCount = 0;

// Get index of location name
int getIndex(char name[], int n) {
    for(int i = 0; i < n; i++) {
        if(strcmp(locations[i], name) == 0)
            return i;
    }
    return -1;
}

// Find with path compression
int find(int x) {
    findCount++;
    if(parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

// Union
void unionSet(int a, int b) {
    unionCount++;
    parent[a] = b;
}

// Sort edges by weight
int compare(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int n, e;

    printf("Enter number of locations and connections:\n");
    scanf("%d %d", &n, &e);

    printf("Enter location names:\n");
    for(int i = 0; i < n; i++) {
        scanf("%s", locations[i]);
    }

    char loc1[50], loc2[50];

    printf("Enter connections (location1 location2 cost):\n");
    for(int i = 0; i < e; i++) {
        scanf("%s %s %d", loc1, loc2, &edges[i].w);

        edges[i].u = getIndex(loc1, n);
        edges[i].v = getIndex(loc2, n);
    }

    // Initialize parent
    for(int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Sort edges (important step)
    qsort(edges, e, sizeof(Edge), compare);

    int totalCost = 0;

    printf("\nSmart City Fiber Network Design\n");
    printf("====================================\n");
    printf("Selected Fiber Connections:\n");

    for(int i = 0; i < e; i++) {
        int pu = find(edges[i].u);
        int pv = find(edges[i].v);

        if(pu != pv) {
            printf("%s <--> %s | Cost: %d\n",
                   locations[edges[i].u],
                   locations[edges[i].v],
                   edges[i].w);

            totalCost += edges[i].w;
            unionSet(pu, pv);
        }
    }

    printf("------------------------------------\n");
    printf("Minimum Total Fiber Cost: %d\n", totalCost);

    // Performance Analysis
    printf("\nPerformance Analysis:\n");
    printf("Find operations: %d\n", findCount);
    printf("Union operations: %d\n", unionCount);
    printf("Time Complexity: O(E log E)\n");

    return 0;
}
