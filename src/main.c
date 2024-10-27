#include <stdio.h>
#include <stdlib.h>

int calculate(int a, int b, int operator) {
    char operators[4] = {'+', '-', '*', '/'};
    switch (operators[operator]) {
        case '+':
            a = a + b;
            break;
        case '-':
            a = a - b;
            break;
        case '*':
            a = a * b;
            break;
        case '/':
            if (b != 0 && a % b == 0) {
                a = a / b;
            } else {
                a = 100000000;  // Just to make the thing not 24
            }
            break;

        default:
            break;
    }

    return a;
}

void searchFor24(int a, int b, int c, int d) {
    char operators[4] = {'+', '-', '*', '/'};
    // printf("%d %d %d %d\n", a, b, c, d);
    for (int i = 0; i < 4; i++) {          // i = First operator
        for (int z = 0; z < 4; z++) {      // z = Second operator
            for (int y = 0; y < 4; y++) {  // y = last operator
                // printf("(%d %c %d) %c (%d %c %d) = %d = %d %c %d\n", a, operators[i], b, operators[z], c, operators[y], d, calculate(calculate(a, b, i), calculate(c, d, y), z), calculate(a, b, i), operators[z], calculate(c, d, y));
                if (calculate(calculate(a, b, i), calculate(c, d, y), z) == 24) {  // (a.b).(c.d) '.' = operator
                    printf("((%d %c %d) %c (%d %c %d))\n", a, operators[i], b, operators[z], c, operators[y], d);
                    exit(EXIT_SUCCESS);
                } else if (calculate(calculate(a, calculate(b, c, z), i), d, y) == 24) {  // (a.(b.c)).d
                    printf("((%d %c (%d %c %d) %c %d)\n", a, operators[i], b, operators[z], c, operators[y], d);
                    exit(EXIT_SUCCESS);
                } else if (calculate(calculate(calculate(a, b, i), c, z), d, y) == 24) {  // (((a.b).c).d)
                    printf("(((%d %c %d) %c %d) %c %d)\n", a, operators[i], b, operators[z], c, operators[y], d);
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
                    if (i1 != i2 && i1 != i3 && i1 != i4 && i2 != i3 && i2 != i4 && i3 != i4 && i4 != i3) {
                        searchFor24(a, b, c, d);
                    }
                }
            }
        }
    }

    printf("No solution\n");
    return 0;
}