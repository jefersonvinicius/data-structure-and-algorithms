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
    append(map->keys[hashed], create_node(value)); 
}

int get(struct HashMap* map, char *key) {
    int hashed = hash(key);
    struct LinkedList* list = map->keys[hashed];
    
    return value;
}

int* values(struct HashMap* map) {
    int* values = malloc(sizeof(int) * MOD);
    int index = 0;
    for (int i = 0; i < MOD; i++) {
        if (map->keys[i] != INT_MIN) {
            values[index] = map->keys[i];
            index++; 
        }
    }
    return values;
}


void debug_hashmap(struct HashMap* map) {
    int found_something = 0;
    for (int i = 0; i < MOD; i++) {
        if (map->keys[i] != INT_MIN) {
            printf("[%d] -> %d\n", i, map->keys[i]);
            found_something = 1;    
        }
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
        assert(map->keys[60] == 10);
        assert(map->keys[24] == 20);
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
        set(map, "key-2", 20);
        int* all_values = values(map);
        assert(all_values[0] == 20);
        assert(all_values[1] == 10);
    }
    
    { // should handle collision using "separate chaining" technique
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        set(map, "fersonej", 20);
        assert(get(map, "fersonej") == 20);
        assert(get(map, "jeferson") == 10);
    }
    

    return 0;
}