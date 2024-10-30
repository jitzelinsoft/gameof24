#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TARGET 24  // Define a constant for the target value

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

                if (result1 == TARGET) {
                    printf("((%d %c %d) %c (%d %c %d))\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                } else if (result2 == TARGET) {
                    printf("((%d %c (%d %c %d)) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                } else if (result3 == TARGET) {
                    printf("(((%d %c %d) %c %d) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
}

int main() {
    int array[4];
    // Inputs into array
    for (int i = 0; i < 4; i++) {
        scanf("%d", &array[i]);
    }

    // Check all possible combinations for a, b, c, d
    int a, b, c, d;
    for (int i = 0; i < 4; i++) {
        a = array[i];
        for (int j = 0; j < 4; j++) {
            if (j == i) continue;
            b = array[j];
            for (int k = 0; k < 4; k++) {
                if (k == i || k == j) continue;
                c = array[k];
                for (int l = 0; l < 4; l++) {
                    if (l == i || l == j || l == k) continue;
                    d = array[l];
                    searchFor24(a, b, c, d);
                }
            }
        }
    }

    printf("No solution\n");
    return 0;
}
