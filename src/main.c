#define NDEBUG
#define MAX 4
#define MAX_STEPS 3
#define COMP_LENGTH 6
#define EXPR_SIZE 14

#include <stdio.h>
#include <string.h>

typedef struct {
    double value;
    char expr[EXPR_SIZE];
} NumberWithExpression;

#ifndef NDEBUG
void debugPrintArray(char *name, NumberWithExpression n[MAX], int length) {
    printf("%s = {", name);
    for (int i = 0; i < length; i++) {
        printf("%.2lf", n[i].value);
        if (i != length - 1) {
            printf(",");
        }
    }
    printf("}\n");
}
#endif /* ifndef NDEBUG */

void computeAnswers(double answers[COMP_LENGTH], char expressions[COMP_LENGTH][EXPR_SIZE], NumberWithExpression x,
                    NumberWithExpression y) {
    answers[0] = x.value + y.value;
    sprintf(expressions[0], "(%s+%s)", x.expr, y.expr);

    answers[1] = x.value - y.value;
    sprintf(expressions[1], "(%s-%s)", x.expr, y.expr);

    answers[2] = y.value - x.value;
    sprintf(expressions[2], "(%s-%s)", y.expr, x.expr);

    answers[3] = x.value * y.value;
    sprintf(expressions[3], "(%s*%s)", x.expr, y.expr);

    answers[4] = x.value / y.value;
    sprintf(expressions[4], "(%s/%s)", x.expr, y.expr);

    answers[5] = y.value / x.value;
    sprintf(expressions[5], "(%s/%s)", y.expr, x.expr);
}

int isAnswerFound(NumberWithExpression n[MAX], int l, char solution[EXPR_SIZE]) {
    // Base case
    if (l == 1) {
        if (n[0].value - 24 >= 0 && n[0].value - 24 < 0.001) {
            strcpy(solution, n[0].expr);
            return 1;
        }
        return 0;
    }

    for (int i = 0; i < l; i++) {
        for (int j = i + 1; j < l; j++) {
#ifndef NDEBUG
            debugPrintArray("numbers", n, l);
#endif /* ifndef NDEBUG */

            // Generate a new array for the function call, but
            // without the numbers that are used in the calculation
            // (index i and j).
            NumberWithExpression new[MAX];
            int index = 1;
            for (int k = 0; k < l; k++) {
                if (k != i && k != j) {
                    new[index] = n[k];
                    index++;
                }
            }

#ifndef NDEBUG
            debugPrintArray("numbers", new, l - 1);
            printf("---\n");
#endif /* ifndef NDEBUG */

            // Compute new answers and new expresions
            double answers[COMP_LENGTH];
            char expressions[COMP_LENGTH][EXPR_SIZE];
            computeAnswers(answers, expressions, n[i], n[j]);

            for (int k = 0; k < COMP_LENGTH; k++) {
                new[0].value = answers[k];
                strcpy(new[0].expr, expressions[k]);
                if (isAnswerFound(new, l - 1, solution)) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    NumberWithExpression n[4];
    char solution[EXPR_SIZE];

    for (int i = 0; i < 4; i++) {
        scanf("%lf", &n[i].value);
        char digit = '0' + (int)n[i].value;
        sprintf(n[i].expr, "%c", digit);
    }

    if (isAnswerFound(n, MAX, solution)) {
        printf("%s\n", solution);
    } else {
        printf("No solution.\n");
    }

    return 0;
}
