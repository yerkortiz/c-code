#include <stdio.h>

#define STACK_SIZE (1 << 4)
#define EXIT_PROGRAM return 0

typedef struct
{
    int elements[STACK_SIZE];
    int top, size;
} stack;
int notEmpty(stack *s)
{  
    return (s->size == 0);
}
void push(stack *s, int value)
{
    if(notEmpty(s)){
        s->elements[(s->top)++] = value;
        s->top = ((s->top) + STACK_SIZE) % STACK_SIZE;
        ++(s->size);
    }
}
void pop(stack *s)
{
    if(notEmpty(s)) {
        s->elements[(s->top)--] = 0;
        s->top = ((s->top) + STACK_SIZE) % STACK_SIZE;
        --(s->size);
    }
}
int top(stack *s)
{
    return (s->elements[s->top]);
}
int main(void)
{
    EXIT_PROGRAM;
}