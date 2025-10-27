// C program to evaluate postfix expressions

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 25

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void getCurrentTime() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    int h = t->tm_hour;
    if (h >= 12) {
        h = h - 12;
    }
    printf("%d:%d:%d : ", h, t->tm_min, t->tm_sec);
}

void initialize(Stack *stack) {
    stack->top = -1;
}

bool isFull(Stack *stack) {
    if (stack->top == MAX - 1) {
        getCurrentTime();
        printf("Stack Full\n");
        return true;
    }
    return false;
}

bool isEmpty(Stack *stack) {
    if (stack->top == -1) {
        getCurrentTime();
        printf("Stack Empty\n");
        return true;
    }
    return false;
}

void Push(Stack *stack, int val) {
    if (isFull(stack)) {
        return;
    }
    stack->arr[++stack->top] = val;
    getCurrentTime();
    printf("Pushed\n");
}

int Pop(Stack *stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    int popped = stack->arr[stack->top];
    stack->top--;
    getCurrentTime();
    printf("Popped\n");
    return popped;
}

int Peep(Stack *stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->arr[stack->top];
}

int PopTwice(Stack *stack) {
    return Pop(stack), Pop(stack);
}

int Eval(Stack *stack, char expression[]) {
    char ch;
    int A = 0, B = 0;
    int res;
    int len = strlen(expression);
    for (int i = 0; i < len; i++) {
        ch = expression[i];
        if (isdigit(ch)) {
            Push(stack, ch - '0');
        } else {
            A = Pop(stack);
            B = Pop(stack);
            switch (ch) {
            case '+':
                res = A + B;
                break;
            case '-':
                res = A - B;
                break;
            case '*':
                res = A * B;
                break;
            case '/':
                res = A / B;
                break;
            default:
                getCurrentTime();
                printf("invalid");
                break;
            }
            Push(stack, res);
        }
    }
    return Pop(stack);
}

int main() {
    Stack stack;
    initialize(&stack);
    char expression[MAX];
    scanf("%s", expression);
    printf("%d", Eval(&stack, expression));
}