#define MAX_SIZE 4

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int calculate(int a, int b, int operator) {
    // Returns a calculation of a and b with the given operator
    switch (operator) {
        case 0:  // '+'
            return a + b;
        case 1:  // '-'
            return a - b;
        case 2:  // '*'
            return a * b;
        case 3:  // '/'
            return (b != 0 && a % b == 0) ? a / b : nan;
        default:
            return nan;
    }
}

void searchFor24(int a, int b, int c, int d) {
    // Searches for a possible 24 with all possible combinations of the operators
    char operators[4] = {'+', '-', '*', '/'};
    for (int firstOp = 0; firstOp < 4; firstOp++) {
        for (int secondOp = 0; secondOp < 4; secondOp++) {
            for (int thirdOp = 0; thirdOp < 4; thirdOp++) {
                int result1 = calculate(calculate(a, b, firstOp), calculate(c, d, thirdOp), secondOp);
                int result2 = calculate(calculate(a, calculate(b, c, secondOp), firstOp), d, thirdOp);
                int result3 = calculate(calculate(calculate(a, b, firstOp), c, secondOp), d, thirdOp);

                if (result1 == 24) {
                    printf("((%d %c %d) %c (%d %c %d))\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                } else if (result2 == 24) {
                    printf("((%d %c (%d %c %d)) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                } else if (result3 == 24) {
                    printf("(((%d %c %d) %c %d) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
}

void swapIndices(int arr[MAX_SIZE], int i, int j) {
}

int main() {
    int nums[MAX_SIZE];
    scanf("%d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3]);

    // Loop over all permutations of the given integer array
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = i + 1; j < MAX_SIZE; j++) {
            int copied[MAX_SIZE] = {nums[0], nums[1], nums[2], nums[3]};
            int t = copied[i];
            copied[i] = copied[j];
            copied[j] = t;
            searchFor24(copied[0], copied[1], copied[2], copied[3]);
        }
    }

    printf("No solution\n");
    return 0;
}
