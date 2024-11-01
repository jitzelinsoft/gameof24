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

void swap(int nums[MAX_SIZE], int i, int j) {
    int t = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
}

int main() {
    int nums[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++) {
        scanf("%d", &nums[i]);
        if (nums[i] < 1 || nums[i] > 10) {
            printf("Invalid input\n");
            return 0;
        }
    }

    int c[4] = {0, 0, 0, 0};

    // Loop over all permutations
    for (int i = 1; i < MAX_SIZE;) {
        if (c[i] < i) {
            if (i % 2) {
                swap(nums, 0, i);
            } else {
                swap(nums, c[i], i);
            }

            // Next permutation available here
            searchFor24(nums[0], nums[1], nums[2], nums[3]);

            c[i] += 1;
            i = 1;
        } else {
            c[i] = 0;
            i++;
        }
    }

    printf("No solution\n");
    return 0;
}
