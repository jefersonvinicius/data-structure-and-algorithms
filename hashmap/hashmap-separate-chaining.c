#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MOD 100

int hash(char* key) {
    int result = 0;
    for (int i = 0; i < strlen(key); i++) {
        result += (int) key[i];
    }
    return result % MOD;
}

struct HashMap {
    int* keys;
};

struct HashMap* create_hashmap() {
    struct HashMap* hashmap = malloc(sizeof(struct HashMap));
    hashmap->keys = malloc(sizeof(int) * MOD);
    memset(hashmap->keys, -20, MOD);
    return hashmap;
}

int get(char* key) {}

int set(struct HashMap* map, char* key, int value) {
    int hashed = hash(key);
    map->keys[hashed] = value;
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

int main() {

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
        debug_hashmap(map);
        assert(map->keys[60] == 10);
    }

    

    return 0;
}