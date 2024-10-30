/*
 * Game of 24 solver:
 * - Cards between 1-9, so division by zero can't exist.
 */

#define MAX_LENGTH 4
#define MAX_STEPS 3
#define COMP_LENGTH 6
#define NDEBUG

#include <stdio.h>

typedef struct {
    double x;
    double y;
    char op;
} Step;

#ifndef NDEBUG
void debugPrintArray(char *name, double arr[4], int length) {
    printf("%s = {", name);
    for (int i = 0; i < length; i++) {
        printf("%.2lf", arr[i]);
        if (i != length - 1) {
            printf(",");
        }
    }
    printf("}\n");
}

void debugPrintSteps(Step s[MAX_STEPS]) {
    printf("Steps = {\n");
    for (int i = 0; i < MAX_STEPS; i++) {
        printf("\t%.2lf %c %.2lf,\n", s[i].x, s[i].op, s[i].y);
    }
    printf("}\n");
}
#endif /* ifndef NDEBUG */

void computeAnswers(double answers[COMP_LENGTH], double x, double y) {
    answers[0] = x + y;
    answers[1] = x - y;
    answers[2] = y - x;
    answers[3] = x * y;
    answers[4] = x / y;
    answers[5] = y / x;
}

void swapIndices(double a[MAX_LENGTH], int x, int y) {
    int t = a[x];
    a[x] = a[y];
    a[y] = t;
}

char getOperator(int k) {
    switch (k) {
        case 0:
            return '+';
        case 1:
        case 2:
            return '-';
        case 3:
            return '*';
        case 4:
        case 5:
            return '/';
    }
    return -1;
}

/*
 * This function returns if a solution to can be found to a 24 game input. In
 * this process it mutates the steps variable to give an explanation about the
 * answer.
 */
int isAnswerFound(double n[MAX_LENGTH], int l, Step steps[MAX_STEPS]) {
#ifndef NDEBUG
    debugPrintArray("numbers", n, l);
#endif /* ifndef NDEBUG */

    // Base case
    if (l == 1) {
        return (n[0] - 24 >= 0 && n[0] - 24 < 0.001);
    }

    for (int i = 0; i < l; i++) {
        for (int j = i + 1; j < l; j++) {
            // Generate a permutation of the original array
            double perm[MAX_LENGTH] = {n[0], n[1], n[2], n[3]};
            swapIndices(perm, i, j);

            // Get all the computations
            double answers[COMP_LENGTH];
            computeAnswers(answers, perm[0], perm[1]);

            double new[MAX_LENGTH];
            for (int k = 0; k < COMP_LENGTH; k++) {
                new[0] = answers[k];
                new[1] = perm[2];
                new[2] = perm[3];

                steps[MAX_LENGTH - l] = (Step){.x = perm[0], .y = perm[1], .op = getOperator(k)};
                if (isAnswerFound(new, l - 1, steps)) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    double n[4];
    scanf("%lf %lf %lf %lf", &n[0], &n[1], &n[2], &n[3]);

    Step s[MAX_STEPS];

    if (isAnswerFound(n, MAX_LENGTH, s)) {
#ifndef NDEBUG
        debugPrintSteps(s);
#endif /* ifndef NDEBUG */
        printf("(((%.0lf%c%.0lf)%c%.0lf)%c%.0lf)\n", s[0].x, s[0].op, s[0].y, s[1].op, s[1].x, s[2].op, s[2].x);
    } else {
        printf("No solution.\n");
    }

    return 0;
}
