#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 10

// rods represented as arrays
int rodA[MAX_DISKS];
int rodB[MAX_DISKS];
int rodC[MAX_DISKS];

// top index for each rod (-1 if empty)
int topA = -1, topB = -1, topC = -1;

// push a disk onto a rod
void push(int rod[], int *top, int disk) {
    rod[++(*top)] = disk;
}

// pop a disk from a rod
int pop(int rod[], int *top) {
    if (*top == -1) return -1;
    return rod[(*top)--];
}

// print all rods
void printRods(int total) {
    printf("\n--- Current Rods ---\n");
    printf("Rod A: ");
    for (int i = 0; i <= topA; i++) printf("%d ", rodA[i]);
    printf("\nRod B: ");
    for (int i = 0; i <= topB; i++) printf("%d ", rodB[i]);
    printf("\nRod C: ");
    for (int i = 0; i <= topC; i++) printf("%d ", rodC[i]);
    printf("\n--------------------\n");
}

// check if game is solved
int checkSolved(int total) {
    if (topC + 1 != total) return 0; // not all disks on C
    for (int i = 0; i < total; i++) {
        if (rodC[i] != total - 1 - i) return 0; // wrong order
    }
    return 1;
}

int main() {
    int total;
    printf("Enter number of disks (1–%d): ", MAX_DISKS);
    scanf("%d", &total);
    if (total < 1 || total > MAX_DISKS) {
        printf("Invalid number of disks.\n");
        return 1;
    }

    // initialize rodA (largest disk = total-1, smallest = 0)
    for (int i = total - 1; i >= 0; i--) {
        push(rodA, &topA, i);
    }

    int moves = 0;
    printRods(total);

    // game loop
    while (!checkSolved(total)) {
        char from, to;
        printf("Move from (A/B/C): ");
        scanf(" %c", &from);
        printf("Move to (A/B/C): ");
        scanf(" %c", &to);

        int *fromRod, *toRod, *fromTop, *toTop;

        // assign rods
        if (from == 'A' || from == 'a') { fromRod = rodA; fromTop = &topA; }
        else if (from == 'B' || from == 'b') { fromRod = rodB; fromTop = &topB; }
        else if (from == 'C' || from == 'c') { fromRod = rodC; fromTop = &topC; }
        else { printf("Invalid rod!\n"); continue; }

        if (to == 'A' || to == 'a') { toRod = rodA; toTop = &topA; }
        else if (to == 'B' || to == 'b') { toRod = rodB; toTop = &topB; }
        else if (to == 'C' || to == 'c') { toRod = rodC; toTop = &topC; }
        else { printf("Invalid rod!\n"); continue; }

        int disk = pop(fromRod, fromTop);
        if (disk == -1) {
            printf("That rod is empty!\n");
            continue;
        }

        // check if move is valid
        if (*toTop != -1 && toRod[*toTop] < disk) {
            printf("Invalid move! Can't place larger disk on smaller one.\n");
            push(fromRod, fromTop, disk); // undo
            continue;
        }

        push(toRod, toTop, disk);
        moves++;
        printRods(total);
    }

    printf("🎉 You solved it in %d moves!\n", moves);
    return 0;
}

