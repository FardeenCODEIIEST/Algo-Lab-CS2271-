//CONNECTED COMPONENTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 2000

int parent[MAX_MEMBERS];
int rank[MAX_MEMBERS];

// Find the root of the subset containing the given element
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// Join the subsets containing the given elements
void union_sets(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);

    if (root_x == root_y) {
        return;
    }

    if (rank[root_x] < rank[root_y]) {
        parent[root_x] = root_y;
    } else if (rank[root_x] > rank[root_y]) {
        parent[root_y] = root_x;
    } else {
        parent[root_y] = root_x;
        rank[root_x]++;
    }
}

int main() {
    // Read membership details from file 1
    FILE *file1 = fopen("/Users/anishbanerjee/Desktop/Algorithm Laboratory/membership.txt", "r");
    if (file1 == NULL) {
        perror("/Users/anishbanerjee/Desktop/Algorithm Laboratory/membership.txt");
        exit(1);
    }

    int num_members = 0;
    while (!feof(file1)) {
        int member_id, department_id;
        fscanf(file1, "%d %d", &member_id, &department_id);

        // Initialize parent array
        parent[member_id] = member_id;
        rank[member_id] = 0;

        num_members++;
    }

    fclose(file1);

    // Read email connectivity details from file 2
    FILE *file2 = fopen("/Users/anishbanerjee/Desktop/Algorithm Laboratory/connectivity.txt", "r");
    if (file2 == NULL) {
        perror("/Users/anishbanerjee/Desktop/Algorithm Laboratory/connectivity.txt");
        exit(1);
    }

    while (!feof(file2)) {
        int member1_id, member2_id;
        fscanf(file2, "%d %d", &member1_id, &member2_id);

        union_sets(member1_id, member2_id);
    }

    fclose(file2);

    // Print connected components
    printf("Number of connected components: ");

    int num_components = 0;
    for (int i = 1; i <= num_members; i++) {
        if (parent[i] == i) {
            num_components++;
        }
    }

    printf("%d\n", num_components);

    printf("Connected components:\n");

    for (int i = 1; i <= num_members; i++) {
        if (parent[i] == i) {
            printf("%d ", i);

            for (int j = i + 1; j <= num_members; j++) {
                if (parent[j] == i) {
                    printf("%d ", j);
                }
            }

            printf("\n");
        }
    }

    return 0;
}
