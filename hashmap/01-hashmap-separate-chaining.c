#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "linkedlist/linkedlist.h"

#define MOD 100

int hash(char* key) {
    int result = 0;
    for (int i = 0; i < strlen(key); i++) {
        result += (int) key[i];
    }
    return result % MOD;
}

struct HashMap {
    struct LinkedList** keys;
};

struct HashMap* create_hashmap() {
    struct HashMap* hashmap = malloc(sizeof(struct HashMap));
    hashmap->keys = malloc(sizeof(struct LinkedList) * MOD);
    for (int i = 0; i < MOD; i++) {
        hashmap->keys[i] = create_linked_list();
    }
    return hashmap;
}

int set(struct HashMap* map, char* key, int value) {
    int hashed = hash(key);
    append(map->keys[hashed], create_node(value, key)); 
}

int get(struct HashMap* map, char *key) {
    int hashed = hash(key);
    struct Node* node = find_by_key(map->keys[hashed], key);
    if (node == NULL) return INT_MIN;
    return node->value;
}

void remove_key(struct HashMap* map, char *key) {
    int hashed = hash(key);
    delete_by_key(map->keys[hashed], key);
}

int* values(struct HashMap* map) {
    int* values = malloc(sizeof(int) * MOD);
    int index = 0;
    for (int i = 0; i < MOD; i++) {
        struct LinkedList* chain = map->keys[i];
        if (is_empty(chain)) continue;
        
        struct Node* node = chain->head;
        while (node != NULL) {
            values[index] = node->value;
            node = node->next;
            index++; 
        }
    }
    return values;
}

int has_key(struct HashMap* map, char* key) {
    int hashed = hash(key);
    struct Node* node = find_by_key(map->keys[hashed], key);
    return node != NULL;
}


void debug_hashmap(struct HashMap* map) {
    int found_something = 0;
    for (int i = 0; i < MOD; i++) {
        struct LinkedList* chain = map->keys[i];
        if (is_empty(chain)) continue;
        
        struct Node* node = chain->head;
        printf("[%d] ", i);
        while (node != NULL) {
            printf("-> (%s) %d ", node->key, node->value);
            node = node->next;
        }
        printf("\n");
        found_something = 1;    
        
    }

    if (!found_something) printf("Map Empty!\n");
}

void debug_array(int* array) {
    for (int i = 0; i < sizeof(array); i++) {
        printf("[%d] (%d)\n", i, array[i]);
    }
}

int main() {

    assert(hash("jeferson") == hash("fersonej"));

    { // should hash correctly

        assert(hash("a") == 97);
        assert(hash("d") == 0);
        assert(hash("dd") == 0);
        assert(hash("dda") == 97);
    }

    { // should create hashmap correctly
        struct HashMap* map = create_hashmap();
        assert(map != NULL);
        assert(map->keys != NULL);
    }

    { // should set key-value at hashmap correctly
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        set(map, "key-2", 20);
        assert(map->keys[60]->head->value == 10);
        assert(map->keys[24]->head->value == 20);
    }

    { // should get value by key correctly
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        assert(get(map, "jeferson") == 10);
        assert(get(map, "not_exists") == INT_MIN);
    }

    { // should get all values from hashmap
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        set(map, "fersonej", 15);
        set(map, "key-2", 20);
        int* all_values = values(map);
        assert(all_values[0] == 20);
        assert(all_values[1] == 10);
        assert(all_values[2] == 15);
    }
    
    { // should handle collision using "separate chaining" technique
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        set(map, "fersonej", 20);
        assert(get(map, "fersonej") == 20);
        assert(get(map, "jeferson") == 10);
    }

    { // should remove key from map
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        remove_key(map, "jeferson");
        assert(get(map, "jeferson") == INT_MIN);
        
        set(map, "jeferson", 10);
        set(map, "fersonej", 20);
        remove_key(map, "fersonej");
        assert(get(map, "jeferson") == 10);
        assert(get(map, "fersonej") == INT_MIN);
    }

    { // should return has or not key correctly
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        set(map, "fersonej", 20);
        assert(has_key(map, "jeferson") == 1);
        assert(has_key(map, "fersonej") == 1);
        assert(has_key(map, "not_exists") == 0);
    }
    

    return 0;
}