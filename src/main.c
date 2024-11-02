#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 4

int calculate(int a, int b, int operator) {
    switch (operator) {
        case 0:  // '+'
            return a + b;
        case 1:  // '-'
            return a - b;
        case 2:  // '*'
            return a * b;
        case 3:  // '/'
            return (b != 0 && a % b == 0) ? a / b : INT_MIN;
        default:
            return INT_MIN;
    }
}

int searchFor24(int a, int b, int c, int d) {
    char operators[4] = {'+', '-', '*', '/'};

    for (int firstOp = 0; firstOp < 4; firstOp++) {
        for (int secondOp = 0; secondOp < 4; secondOp++) {
            for (int thirdOp = 0; thirdOp < 4; thirdOp++) {
                int result1 = calculate(calculate(a, b, firstOp), calculate(c, d, thirdOp), secondOp);
                int result2 = calculate(calculate(a, calculate(b, c, secondOp), firstOp), d, thirdOp);
                int result3 = calculate(calculate(calculate(a, b, firstOp), c, secondOp), d, thirdOp);

                if (result1 == 24) {
                    printf("((%d %c %d) %c (%d %c %d))\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    return 1;
                } else if (result2 == 24) {
                    printf("((%d %c (%d %c %d)) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    return 1;
                } else if (result3 == 24) {
                    printf("(((%d %c %d) %c %d) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    return 1;
                }
            }
        }
    }
    return 0;
}

void swap(int nums[MAX_SIZE], int i, int j) {
    int t = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
}

void findPermutations(int nums[MAX_SIZE]) {
    int c[MAX_SIZE] = {0};

    for (int i = 1; i < MAX_SIZE;) {
        if (c[i] < i) {
            swap(nums, (i % 2) ? 0 : c[i], i);
            if (searchFor24(nums[0], nums[1], nums[2], nums[3])) return;

            c[i]++;
            i = 1;
        } else {
            c[i] = 0;
            i++;
        }
    }

    printf("No solution\n");
}

int main() {
    int nums[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++) {
        if (scanf("%d", &nums[i]) != 1 || nums[i] < 1 || nums[i] > 10) {
            printf("Invalid input\n");
            return 0;
        }
    }

    findPermutations(nums);
    return 0;
}
