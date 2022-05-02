#include "../stack/charstack.h"
#include <ctype.h>

int _char_is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


int _get_operator_precedence(char operator) {
    // printf("OPERATOR: %c %d\n", operator, operator == '+');
    if (operator == '+' || operator == '-') return 1;
    if (operator == '*' || operator == '/') return 2;
    if (operator == '^') return 3;
    return -1;
}

void _append_str(char *post_fix[], char *to_append, int* current_postfix_index) {
    printf("Apeending: %s\n", to_append);
    post_fix[*current_postfix_index] = to_append;
    (*current_postfix_index)++;
}

void _pop_until_last_left_parentesis(struct StackNode **stack, char *post_fix[], int *current_postfix_index) {
    while (!is_empty(*stack)) {
        char* popped = pop(stack);
        printf("Popped: %s\n", popped);
        if (strcmp(popped, "(") == 0) break;
        _append_str(post_fix, popped, current_postfix_index);
    }
}

void _pop_until_find_operator_have_less_precedence_than_current_operator_and_push_it(char current_operator, struct StackNode** stack, char *post_fix[], int *current_postfix_index) {
    int current_operator_precedence = _get_operator_precedence(current_operator);
    while (!is_empty(*stack) && current_operator_precedence <= _get_operator_precedence(*top(*stack))) {
        _append_str(post_fix, pop(stack), current_postfix_index);
    }
    push(stack, current_operator);
}

char* _extract_number_digits(const char* str, int start_index) {
    char* result = malloc(0);
    int index = start_index;
    while (isdigit(str[index])) {
        char digit[] = {str[index]};
        strcat(result, digit);
        index++;
    }
    return result;
}

#define STRING_MAX 100

char** infix_to_postfix(const char* infix_expression) {
    int postfix_index = 0;
    char **post_fix;
    post_fix = malloc(strlen(infix_expression) * sizeof(char*));
    for (int i = 0; i < strlen(infix_expression); i++) {
        post_fix[i] = malloc(STRING_MAX * sizeof(char));
    }
    struct StackNode *stack = NULL;
    
    for (int i = 0; i < strlen(infix_expression); i++) {
        char current_char = infix_expression[i];
        if (current_char == ' ') continue;

        if (_char_is_letter(current_char)) {
            printf("%c is letter\n", current_char);
            _append_str(post_fix, &current_char, &postfix_index);
        } else if (isdigit(current_char)) {
            printf("%c is digit\n", current_char);
            char* extracted = _extract_number_digits(infix_expression, i);
            i += (strlen(extracted) - 1);
            printf("extracted: %s len(%ld)\n", extracted, strlen(extracted));
            _append_str(post_fix, extracted, &postfix_index);
        } else if (current_char == '(') {
            push(&stack, current_char);
        } else if (current_char == ')') {
            // printf("Aqui1\n");
            printf("START Popping\n");
            _pop_until_last_left_parentesis(&stack, post_fix, &postfix_index);
            printf("END Popping\n");
        } else {
            // printf("Aqui2\n");
            _pop_until_find_operator_have_less_precedence_than_current_operator_and_push_it(current_char, &stack, post_fix, &postfix_index);   
        }
    }

    // printf("Saiu\n");

    while (!is_empty(stack)) {
        _append_str(post_fix, pop(&stack), &postfix_index);
    }
    
    return post_fix;
}
