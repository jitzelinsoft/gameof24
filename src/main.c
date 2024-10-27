#include <stdio.h>

int Calculate(int a, int b, int operator) {
    char operators[4] = {'+', '-', '*', "/"};
    switch (operator) {
        case '+':
            a = a + b;
            break;
        case '-':
            a = a - b;
            break;
        case '*':
            a = a * b;
        case '/':
            a = a / b;
            break;

        default:
            break;
    }

    return a;
}

int main(int argc, char *argv[]) {
    /* Inputs into array */
    int array[4];
    for (int i = 0; i < 4; i++) {
        scanf("%d", &array[i]);
    }

    /* Outputs all possible combinations for a b c d */
    int a, b, c, d;
    for (int i = 0; i < 4; i++) {
        a = array[i];
        for (int i = 0; i < 4; i++) {
            b = array[i];
            for (int i = 0; i < 4; i++) {
                c = array[i];
                for (int i = 0; i < 4; i++) {
                    d = array[i];
                    if (a != b && a != c && a != d && b != a && b != c && b != d && c != a && c != b && c != d && d != a && d != b && d != c) {  // Non optimized if statement
                        printf("%d %d %d %d\n", a, b, c, d);
                    }
                }
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int z = 0; z < 4; z++) {
            for (int y = 0; y < 4; y++) {
            }
        }
    }
    printf("No solution\n");
    return 0;
}

/*
a[0][1][2][3]
a[1][0][2][3]
a[1][2][0][3]
a[1][2][3][0]
a[2][1][3][0]
a[2][3][1][0]
a[2][3][0][1]
a[3][2][0][1]
a[3][0][2][1]
a[3][0][1][2]
a[0][3][1][2]
a[0][1][3][2]
a[0][1][2][3]

a[0][1][2][3]
a[1][0][2][3]
a[1][2][0][3]
a[1][2][3][0]
a[0][2][3][1]
a[2][0][3][1]
a[2][3][0][1]
a[2][3][1][0]
a[0][3][1][2]
a[3][0][1][2]
a[0][3][1][2]
a[0][1][3][2]
a[0][1][2][3]
a[3][1][2][0]
a[1][3][2][0]
a[1][2][3][0]
a[1][2][0][3]
a[3][2][0][1]
a[2][3][0][1]
a[2][0][3][1]
a[1][0][3][2]
a[0][1][3][2]

a[0][1][2][3]
a[1][0][2][3]
a[2][1][0][3]
a[3][1][2][0]
a[1][0][2][3]
a[0][1][2][3]
a[0][2][1][3]
a[0][3][2][1]
a[2][1][0][3]
a[0][2][1][3]
a[0][1][2][3]
a[0][1][3][2]
a[3][1][2][0]
a[0][3][2][1]
a[0][1][3][2]
a[0][1][2][3]


1 2 3 4
1 2 4 3
1 3 2 4
1 3 4 2
1 4 2 3
1 4 3 2
2 1 3 4
2 1 4 3
2 3 1 4
2 3 4 1
2 4 1 3
2 4 3 1
3 1 2 4
3 1 4 2
3 2 1 4
3 2 4 1
3 4 1 2
3 4 2 1
4 1 2 3
4 1 3 2
4 2 1 3
4 2 3 1
4 3 1 2
4 3 2 1
*/