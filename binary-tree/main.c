#include <stdio.h>
#include <assert.h>
#include "../_utils_/asserts.h"

#include "tree.h"

int main() {

    { // create node correctly
        struct Node* node = create_node(2);
        assert(node->value == 2);
        assert(node->left == NULL);
        assert(node->right == NULL);
    }

    { // create tree correctly
        struct Tree* tree = create_binary_tree();
        assert(tree->root == NULL);
    }

    { // attach child correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(0);
        tree->root->right = create_node(1);
        tree->root->left = create_node(2);
        assert(tree->root->value == 0);
        assert(tree->root->right->value == 1);
        assert(tree->root->left->value == 2);
    }

    { // should get size correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(0);
        tree->root->right = create_node(1);
        tree->root->left = create_node(2);
        tree->root->left->left = create_node(3);
        tree->root->left->right = create_node(10);
        tree->root->right->left = create_node(11);
        assert(tree_size(tree) == 6);
    }

    { // should get in order transversal correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(1);
        tree->root->left = create_node(2);
        tree->root->right = create_node(3);
        tree->root->left->left = create_node(4);
        tree->root->left->right = create_node(5);
        tree->root->right->left = create_node(6);

        int* result = in_order(tree);
        int expected[] = {4, 2, 5, 1, 6, 3};
        assertArray(result, expected, 6);
    }

    { // should get pre order transversal correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(1);
        tree->root->left = create_node(2);
        tree->root->right = create_node(3);
        tree->root->left->left = create_node(4);
        tree->root->left->right = create_node(5);
        tree->root->right->left = create_node(6);

        int* result = pre_order(tree);
        int expected[] = {1, 2, 4, 5, 3, 6};
        assertArray(result, expected, 6);
    }

    { // should get post order transversal correctly
        struct Tree* tree = create_binary_tree();
        tree->root = create_node(1);
        tree->root->left = create_node(2);
        tree->root->right = create_node(3);
        tree->root->left->left = create_node(4);
        tree->root->left->right = create_node(5);
        tree->root->right->left = create_node(6);

        int* result = post_order(tree);
        int expected[] = {4, 5, 2, 6, 3, 1};
        assertArray(result, expected, 6);
    }

    { // should build tree from in order and pre order
        int in_order_data[] = {4, 2, 5, 1, 6, 3};
        int pre_order_data[] = {1, 2, 4, 5, 3, 6};
        struct Tree* tree = build_tree_from_pre_and_in_order(pre_order_data, in_order_data, 6);
        assert(tree->root->value == 1);
        assert(tree->root->left->value == 2);
        assert(tree->root->right->value == 3);
        assert(tree->root->left->left->value == 4);
        assert(tree->root->left->right->value == 5);
        assert(tree->root->right->left->value == 6);
    }

    { // should build tree from in order and pre order with one element
        int in_order_data[] = {1};
        int pre_order_data[] = {1};
        struct Tree* tree = build_tree_from_pre_and_in_order(pre_order_data, in_order_data, 1);
        assert(tree->root->value == 1);
        assert(tree->root->left == NULL);
        assert(tree->root->right == NULL);
    }   

    { // should build tree from expression
        struct TreeChar* tree = build_tree_expression("4 * a - ( 6 + b ) + 8 / ( 9 - 7 )");
        assert(strcmp(tree->root->value, "+") == 0);
        assert(strcmp(tree->root->left->value, "-") == 0);
        assert(strcmp(tree->root->right->value, "/") == 0);
        assert(strcmp(tree->root->left->left->value, "*") == 0);    
        assert(strcmp(tree->root->left->right->value, "+") == 0);   
        assert(strcmp(tree->root->right->left->value, "8") == 0); 
        assert(strcmp(tree->root->right->right->value, "-") == 0);
        assert(strcmp(tree->root->left->left->left->value, "4") == 0); 
        assert(strcmp(tree->root->left->left->right->value, "a") == 0);
        assert(strcmp(tree->root->left->right->left->value, "6") == 0);   
        assert(strcmp(tree->root->left->right->right->value, "b") == 0);
        assert(strcmp(tree->root->right->right->left->value, "9") == 0);   
        assert(strcmp(tree->root->right->right->right->value, "7") == 0);   
    }

    { // should build tree from expression with number bigger then 1
        struct TreeChar* tree = build_tree_expression("40 * a - ( 600 + b ) + 8540 / ( 90 - 7 )");
        assert(strcmp(tree->root->value, "+") == 0);
        assert(strcmp(tree->root->left->value, "-") == 0);
        assert(strcmp(tree->root->right->value, "/") == 0);
        assert(strcmp(tree->root->left->left->value, "*") == 0);    
        assert(strcmp(tree->root->left->right->value, "+") == 0);   
        assert(strcmp(tree->root->right->left->value, "8540") == 0); 
        assert(strcmp(tree->root->right->right->value, "-") == 0);
        assert(strcmp(tree->root->left->left->left->value, "40") == 0); 
        assert(strcmp(tree->root->left->left->right->value, "a") == 0);
        assert(strcmp(tree->root->left->right->left->value, "600") == 0);   
        assert(strcmp(tree->root->left->right->right->value, "b") == 0);
        assert(strcmp(tree->root->right->right->left->value, "90") == 0);   
        assert(strcmp(tree->root->right->right->right->value, "7") == 0);   
    }


    { // should evaluate tree expression correctly
        int result = solve_expression_with_tree("1 + 2 * 2 - 1 + (6 / 2 + 1)");
        assert(result == 8);
    }

    { // should evaluate tree expression correctly event with numbers with more than 1 digit
        int result = solve_expression_with_tree("112 + 23 * (22 - 10) + (602 / 2 + 10)");
        assert(result == 699);
        assert(solve_expression_with_tree("20 / 20") == 1);
        assert(solve_expression_with_tree("20 * 20") == 400);
        assert(solve_expression_with_tree("2 * 2 + 100021121") == 100021125);
    }

    { // should print the tree correctly
        struct TreeChar* tree = build_tree_expression("40 * a - ( 600 + b ) + 8540 / ( 90 - 7 )");
        printf("Printing tree:\n");
        print_tree(tree);
    }

    return 0;
}