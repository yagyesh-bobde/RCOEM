#include <stdio.h>
#include <stdlib.h>

#define SIZE 3


int countMissingTiles(int source[SIZE][SIZE], int target[SIZE][SIZE]) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (source[i][j] != target[i][j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int source[SIZE][SIZE] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    
    int randomGrid[SIZE][SIZE] = {{1, 2, 3}, {7, 8, 0}, {4, 5, 6}};

    printf("Source Array:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", source[i][j]);
        }
        printf("\n");
    }

    printf("\nTarget Array:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", randomGrid[i][j]);
        }
        printf("\n");
    }

    int missingTiles = countMissingTiles(source, randomGrid);
    printf("\nNumber of missing tiles: %d\n", missingTiles);

    return 0;
}
