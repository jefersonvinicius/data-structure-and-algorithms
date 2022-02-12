#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "hashmap-open-dressing-node/node.h"

#define TABLE_SIZE 100

int hash(char* key) {
    int result = 0;
    for (int i = 0; i < strlen(key); i++) {
        result += (int) key[i];
    }
    return result % TABLE_SIZE;
}

struct HashMap {
    struct Node** keys;
};

struct HashMap* create_hashmap() {
    struct HashMap* hashmap = malloc(sizeof(struct HashMap));
    hashmap->keys = malloc(sizeof(struct Node) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashmap->keys[i] = NULL;
    }
    return hashmap;
}

int set(struct HashMap* map, char* key, int value) {
    int hashed = hash(key);
    struct Node* node = create_node(key, value);
    int count = hashed;
    while (count < TABLE_SIZE) {
        if (map->keys[count] == NULL) {
            map->keys[count] = node;
            break;
        } else if (strcmp(map->keys[count]->key, key) == 0) {
            map->keys[count]->value = value;    
            break;
        } else {
            count++;
        }
    }
    
}

int get(struct HashMap* map, char *key) {
    int hashed = hash(key);
    int count = hashed;
    while (count < TABLE_SIZE) {
        if (map->keys[count] != NULL && strcmp(map->keys[count]->key, key) == 0) {
            return map->keys[count]->value;
        } else {
            count++;
        }
    }
    return INT_MIN;
}

void remove_key(struct HashMap* map, char *key) {
    int hashed = hash(key);
    int count = hashed;
    while (count < TABLE_SIZE) {
        if (strcmp(map->keys[count]->key, key) == 0) {
            struct Node* hold = map->keys[count];
            map->keys[count] = NULL;
            free(hold);
            break;
        } else {
            count++;
        }
    }
}

int* values(struct HashMap* map) {
    int* values = malloc(sizeof(int) * TABLE_SIZE);
    int index = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (map->keys[i] != NULL) {
            values[index] = map->keys[i]->value;
            index++;
        }
    }
    return values;
}

int has_key(struct HashMap* map, char* key) {
    int hashed = hash(key);
    int count = hashed;
    while (count < TABLE_SIZE) {
        if (map->keys[count] != NULL && strcmp(map->keys[count]->key, key) == 0) {
            return 1;
        } else {
            count++;
        }
    }
    return 0;
}


void debug_hashmap(struct HashMap* map) {
    int found_something = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (map->keys[i] != NULL) {
            printf("[%d] - (%s) %d\n", i, map->keys[i]->key, map->keys[i]->value);
            found_something = 1;
        }
    }

    if (!found_something) printf("Map Empty!\n");
}

void debug_array(int* array) {
    for (int i = 0; i < TABLE_SIZE; i++) {
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
        assert(map->keys[60]->value == 10);
        assert(map->keys[24]->value == 20);
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
    
    { // should handle collision using "open addressing" technique
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        set(map, "fersonej", 20);
        assert(get(map, "fersonej") == 20);
        assert(get(map, "jeferson") == 10);
        assert(map->keys[60]->value == 10);
        assert(map->keys[61]->value == 20);
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
        debug_hashmap(map);
    }

    { // should override when set the same key
        struct HashMap* map = create_hashmap();
        set(map, "jeferson", 10);
        set(map, "jeferson", 20);
        int hashed = hash("jeferson");
        assert(has_key(map, "jeferson") == 1);
        assert(get(map, "jeferson") == 20);
        remove_key(map, "jeferson");
        assert(has_key(map, "jeferson") == 0);
    }
    

    return 0;
}