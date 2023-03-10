#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct stack{
    int top;
    unsigned capacity;
    int* array;
};
struct stack* createStack(unsigned capacity){
    struct stack* stack=(struct stack*)malloc(sizeof(struct stack));
    if(!stack){
        return NULL;
    }
    stack->top=-1;
    stack->capacity=capacity;
    stack->array=(int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
int isEmpty(struct stack* stack){
    return (stack->top==-1);
}
char peek(struct stack* stack){
    return(stack->array[stack->top]);
}
char pop(struct stack* stack){
    if(!isEmpty(stack)){
        return(stack->array[stack->top--]);
    }
    return '$';
}
void push(struct stack* stack,char op){
    stack->array[++stack->top]=op;
}
int isOperand(char ch){
    return ((ch>='a' && ch<='z')||(ch>='A' && ch<='Z'));
}
int Prec(char ch){
    switch(ch){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}
int infixTopostfix(char* exp){
    int i,k;
    struct stack* stack=createStack(strlen(exp));
    if(!stack){
        return -1;
    }
    for(i=0,k=-1;exp[i];++i){
        if(isOperand(exp[i])){
            exp[++k]=exp[i];
        }
        else if(exp[i]=='('){
            push(stack,exp[i]);
        }
        else if(exp[i]==')'){
            while(!isEmpty(stack)&&peek(stack)!='('){
                exp[++k]=pop(stack);
            }
            if(!isEmpty(stack)&&peek(stack)!='('){
                return -1;
            }
            else{
                pop(stack);
            }
        }
        else{
            while(!isEmpty(stack) && Prec(exp[i])<=Prec(peek(stack))){
                exp[++k]=pop(stack);
            }
            push(stack,exp[i]);
        }
    }
    while(!isEmpty(stack)){
        exp[++k]=pop(stack);
    }
    exp[++k]='\0';
    printf("%s",exp);
}
int main(){
    char exp[100];
    printf("Enter an expression: ");
    scanf("%s",exp);
    infixTopostfix(exp);
    printf("\n");
    return 0;
}