/*
 * Game of 24 solver:
 * - Cards between 1-9, so division by zero can't exist.
 */

#define MAX_LENGTH 4
#define MAX_STEPS 3
#define COMP_LENGTH 6
// #define NDEBUG

#include <stdio.h>

typedef struct {
    char operator;
    double num;
} Step;

typedef struct {
    double firstNum;
    Step data[MAX_STEPS];
    int currentSteps;
} Steps;

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

void debugPrintSteps(Steps s) {
    printf("s.firstNum = %.2lf\n", s.firstNum);
    for (int i = 0; i < MAX_STEPS; i++) {
        printf("s.step[i].operator = '%c'\n", s.data[i].operator);
        printf("s.step[i].num = %2.lf\n", s.data[i].num);
    }
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

void addStep(Steps *s, double num, char operator) {
    s->data[s->currentSteps] = (Step){.num = num, .operator= operator};
    s->currentSteps++;
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

void answer(double numbers[MAX_LENGTH], int length, Steps *s, int *found) {
    if (*found == 1) {
        return;
    }

    if (length == 1 && (int)numbers[0] == 24) {
        *found = 1;
        return;
    }

    Steps cSteps = *s;

    // Loop over all permuatations
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            // Create the permuatation
            double perm[MAX_LENGTH] = {numbers[0], numbers[1],
                                       numbers[2], numbers[3]};
            swapIndices(perm, i, j);
#ifndef NDEBUG
            debugPrintArray("perm", perm, length);
#endif /* ifndef NDEBUG */

            if (length == 4) {
                cSteps.firstNum = perm[0];
            }

            // Calculate all possible computations
            double answers[COMP_LENGTH];
            computeAnswers(answers, perm[0], perm[1]);

            // Call this function recursively with a new array
            for (int k = 0; k < COMP_LENGTH; k++) {
                Steps ccSteps = cSteps;

                double new[MAX_LENGTH];
                new[0] = answers[k];
                new[1] = perm[2];
                new[2] = perm[3];

                addStep(&ccSteps, perm[1], getOperator(k));
#ifndef NDEBUG
                debugPrintArray("new", new, length - 1);
#endif /* ifndef NDEBUG */
                answer(new, length - 1, &ccSteps, found);

                if (*found) {
                    *s = ccSteps;
                    return;
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    double n[4];
    int found = 0;
    scanf("%lf %lf %lf %lf", &n[0], &n[1], &n[2], &n[3]);

    Steps s;
    s.currentSteps = 0;
    answer(n, MAX_LENGTH, &s, &found);

#ifndef NDEBUG
    debugPrintSteps(s);
#endif /* ifndef NDEBUG */
    if (found) {
        printf("(((%.0lf%c%.0lf)%c%.0lf)%c%.0lf)\n", s.firstNum,
               s.data[0].operator, s.data[0].num, s.data[1].operator,
               s.data[1].num, s.data[2].operator, s.data[2].num);
    } else {
        printf("No solution.\n");
    }

    return 0;
}
