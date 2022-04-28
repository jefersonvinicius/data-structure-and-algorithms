#include "../stack/charstack.h"


int _char_is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int _char_is_digit(char c) {
    return c >= '0' && c <= '9';
}

int _get_operator_precedence(char operator) {
    if (operator == '+' || operator == '-') return 1;
    if (operator == '*' || operator == '/') return 2;
    if (operator == '^') return 3;
    return -1;
}

void _append_char(char *str, char c) {
    int newSize = (strlen(str) + 2); 
    str = (char *) realloc(str, newSize);
    char cater[] = {c};
    strcat(str, cater);
}

void _pop_until_last_left_parentesis(struct StackNode **stack, char *post_fix) {
    while (!is_empty(*stack)) {
        char* popped = pop(stack);
        if (*popped == '(') break;
        _append_char(post_fix, *popped);
    }
}

void _pop_until_find_operator_have_less_precedence_than_current_operator_and_push_it(char current_operator, struct StackNode** stack, char *post_fix) {
    int current_operator_precedence = _get_operator_precedence(current_operator);
    while (!is_empty(*stack) && current_operator_precedence <= _get_operator_precedence(*top(*stack))) {
        _append_char(post_fix, *pop(stack));
    }
    push(stack, current_operator);
}

const char* infix_to_postfix(const char* infixExpression) {
    char *postFix = malloc(0);
    struct StackNode *stack = NULL;
    
    for (int i = 0; i < strlen(infixExpression); i++) {
        char current_char = infixExpression[i];
        if (current_char == ' ') continue;

        if (_char_is_digit(current_char) || _char_is_letter(current_char)) {
            _append_char(postFix, current_char);
        } else if (current_char == '(') {
            push(&stack, current_char);
        } else if (current_char == ')') {
            _pop_until_last_left_parentesis(&stack, postFix);
        } else {
            _pop_until_find_operator_have_less_precedence_than_current_operator_and_push_it(current_char, &stack, postFix);   
        }
    }

    while (!is_empty(stack)) {
        _append_char(postFix, *pop(&stack));
    }
    
    return postFix;
}
