#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StackNode {
    char value;
    struct StackNode* next;
};

struct StackNode* create_node(char value) {
    struct StackNode* node = malloc(sizeof(struct StackNode));
    node->value = value;
    node->next = NULL;
    return node;
}

int is_empty(struct StackNode* rootNode) {  
    return rootNode == NULL;
}

void push(struct StackNode** rootNode, char value) {
    if (*rootNode == NULL) {
        *rootNode = create_node(value);
        return;
    }

    struct StackNode* node = create_node(value);
    node->next = *rootNode;
    *rootNode = node;
}

char top(struct StackNode *rootNode) {
    if (is_empty(rootNode)) {
        printf("ERROR ON TOP: empty stack\n");
        exit(EXIT_FAILURE);    
    }
    return rootNode->value;
}

char pop(struct StackNode **rootNode) {
    if (is_empty(*rootNode)) {
        printf("ERROR ON POP: empty stack\n");
        exit(EXIT_FAILURE);    
    }

    char valuePopped = (*rootNode)->value;
    *rootNode = (*rootNode)->next;
    return valuePopped;
}

int char_is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int char_is_digit(char c) {
    return c >= '0' && c <= '9';
}

int get_operator_precedence(char operator) {
    if (operator == '+' || operator == '-') return 1;
    if (operator == '*' || operator == '/') return 2;
    if (operator == '^') return 3;
    return -1;
}


void append_char(char *str, char c) {
    int newSize = (strlen(str) + 2); 
    str = (char *) realloc(str, newSize);
    char cater[] = {c};
    strcat(str, cater);
}

void pop_until_last_left_parentesis(struct StackNode **stack, char *post_fix) {
    while (!is_empty(*stack)) {
        char popped = pop(stack);
        if (popped == '(') break;
        append_char(post_fix, popped);
    }
}

void pop_until_find_operator_have_less_precedence_than_current_operator_and_push_it(char current_operator, struct StackNode** stack, char *post_fix) {
    int current_operator_precedence = get_operator_precedence(current_operator);
    while (!is_empty(*stack) && current_operator_precedence <= get_operator_precedence(top(*stack))) {
        append_char(post_fix, pop(stack));
    }
    push(stack, current_operator);
}

const char* infix_to_postfix(const char* infixExpression) {
    char *postFix = malloc(0);
    struct StackNode *stack = NULL;
    
    for (int i = 0; i < strlen(infixExpression); i++) {
        char current_char = infixExpression[i];
        if (char_is_digit(current_char) || char_is_letter(current_char)) {
            append_char(postFix, current_char);
        } else if (current_char == '(') {
            push(&stack, current_char);
        } else if (current_char == ')') {
            pop_until_last_left_parentesis(&stack, postFix);
        } else {
            pop_until_find_operator_have_less_precedence_than_current_operator_and_push_it(current_char, &stack, postFix);   
        }
    }

    while (!is_empty(stack)) {
        append_char(postFix, pop(&stack));
    }
    
    return postFix;
}

int main() {

    char expression1[] = "a-b";
    char expression2[] = "a-b*c";
    char expression3[] = "(a-b)*c";
    char expression4[] = "a+b*c^d-e";
    char expression5[] = "a*(b+c)*(d-g)*h";
    char expression6[] = "a*b-c*d^e/f+g*h";

    printf("infix: %s - postfix: %s\n", expression1, infix_to_postfix(expression1));
    printf("infix: %s - postfix: %s\n", expression2, infix_to_postfix(expression2));
    printf("infix: %s - postfix: %s\n", expression3, infix_to_postfix(expression3));
    printf("infix: %s - postfix: %s\n", expression4, infix_to_postfix(expression4));
    printf("infix: %s - postfix: %s\n", expression5, infix_to_postfix(expression5));
    printf("infix: %s - postfix: %s\n", expression6, infix_to_postfix(expression6));
}