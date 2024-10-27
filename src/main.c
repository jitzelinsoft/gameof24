#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int calculate(int a, int b, int operator) {
    /* Returns a calculation from a and b with the given operator */
    switch (operator) {
        case 0:  // '+'
            a = a + b;
            break;
        case 1:  // '-'
            a = a - b;
            break;
        case 2:  // '*'
            a = a * b;
            break;
        case 3:  // '/'
            if (b != 0 && a % b == 0) {
                a = a / b;
            } else {
                a = nan;
            }
            break;
    }
    return a;
}

void searchFor24(int a, int b, int c, int d) {
    /* Searcher for a possible 24 with all possible combinations of the operators */
    char operators[4] = {'+', '-', '*', '/'};
    for (int firstOp = 0; firstOp < 4; firstOp++) {                                                   // First operator
        for (int secondOp = 0; secondOp < 4; secondOp++) {                                            // Second operator
            for (int thirdOp = 0; thirdOp < 4; thirdOp++) {                                           // Third operator
                if (calculate(calculate(a, b, firstOp), calculate(c, d, thirdOp), secondOp) == 24) {  // (a.b).(c.d) --> '.' = operator
                    printf("((%d %c %d) %c (%d %c %d))\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                } else if (calculate(calculate(a, calculate(b, c, secondOp), firstOp), d, thirdOp) == 24) {  // (a.(b.c)).d --> '.' = operator
                    printf("(((%d %c (%d %c %d)) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                } else if (calculate(calculate(calculate(a, b, firstOp), c, secondOp), d, thirdOp) == 24) {  // (((a.b).c).d) --> '.' = operator
                    printf("(((%d %c %d) %c %d) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int array[4];
    /* Inputs into array */
    for (int i = 0; i < 4; i++) {
        scanf("%d", &array[i]);
    }

    /* Checks for all possible combinations for a b c d */
    int a, b, c, d;
    for (int i = 0; i < 4; i++) {
        a = array[i];
        for (int j = 0; j < 4; j++) {
            b = array[j];
            for (int k = 0; k < 4; k++) {
                c = array[k];
                for (int l = 0; l < 4; l++) {
                    d = array[l];
                    if (i != j && i != k && i != l && j != k && j != l && k != l) {  // Checks if a, b, c or d are not referencing to the same variable
                        searchFor24(a, b, c, d);
                    }
                }
            }
        }
    }

    printf("No solution\n");
    return 0;
}