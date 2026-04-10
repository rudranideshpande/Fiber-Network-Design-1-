#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    int u, v, w;
} Edge;

Edge edges[MAX];
char locations[MAX][50];
int parent[MAX];

int findCount = 0;
int unionCount = 0;

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

// Sort edges
int compare(const void* a, const void* b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int n, e;
    char line[200];

    // Read first line
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d %d", &n, &e);

    // Read locations
    fgets(line, sizeof(line), stdin);
    char *token = strtok(line, " \n");
    for(int i = 0; i < n && token != NULL; i++) {
        strcpy(locations[i], token);
        token = strtok(NULL, " \n");
    }

    // Read edges
    for(int i = 0; i < e; i++) {
        fgets(line, sizeof(line), stdin);

        char loc1[50], loc2[50];
        sscanf(line, "%s %s %d", loc1, loc2, &edges[i].w);

        edges[i].u = getIndex(loc1, n);
        edges[i].v = getIndex(loc2, n);

        if(edges[i].u == -1 || edges[i].v == -1) {
            printf("Invalid location name!\n");
            return 0;
        }
    }

    // Initialize parent
    for(int i = 0; i < n; i++)
        parent[i] = i;

    // Sort edges
    qsort(edges, e, sizeof(Edge), compare);

    int totalCost = 0;

    printf("Smart City Fiber Network Design\n");
    printf("====================================\n");

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

    printf("\nPerformance Analysis:\n");
    printf("Find operations: %d\n", findCount);
    printf("Union operations: %d\n", unionCount);
    printf("Time Complexity: O(E log E)\n");

    return 0;
}
