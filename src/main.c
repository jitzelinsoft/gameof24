#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int calculate(int a, int b, int operator) {
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
    char operators[4] = {'+', '-', '*', '/'};
    for (int firstOp = 0; firstOp < 4; firstOp++) {                                                   // First operator
        for (int secondOp = 0; secondOp < 4; secondOp++) {                                            // Second operator
            for (int thirdOp = 0; thirdOp < 4; thirdOp++) {                                           // Third operator
                if (calculate(calculate(a, b, firstOp), calculate(c, d, thirdOp), secondOp) == 24) {  // (a.b).(c.d) '.' = operator
                    printf("((%d %c %d) %c (%d %c %d))\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                } else if (calculate(calculate(a, calculate(b, c, secondOp), firstOp), d, thirdOp) == 24) {  // (a.(b.c)).d
                    printf("((%d %c (%d %c %d) %c %d)\n", a, operators[firstOp], b, operators[secondOp], c, operators[thirdOp], d);
                    exit(EXIT_SUCCESS);
                } else if (calculate(calculate(calculate(a, b, firstOp), c, secondOp), d, thirdOp) == 24) {  // (((a.b).c).d)
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

    /* Outputs all possible combinations for a b c d */
    int a, b, c, d;
    for (int i1 = 0; i1 < 4; i1++) {
        a = array[i1];
        for (int i2 = 0; i2 < 4; i2++) {
            b = array[i2];
            for (int i3 = 0; i3 < 4; i3++) {
                c = array[i3];
                for (int i4 = 0; i4 < 4; i4++) {
                    d = array[i4];
                    if (i1 != i2 && i1 != i3 && i1 != i4 && i2 != i3 && i2 != i4 && i3 != i4) {
                        searchFor24(a, b, c, d);
                    }
                }
            }
        }
    }

    printf("No solution\n");
    return 0;
}