#include "hashmap.h"

hashmap_t* init_hashmap_malloc(size_t length, int (*p_hash_func)(const char* key))
{
    size_t i = 0;
    hashmap_t* result = malloc(sizeof(hashmap_t));
    node_t** bucket = malloc(sizeof(node_t*) * length);
    result->hash_func = p_hash_func;
    for (i = 0; i < length; ++i) {
        bucket[i] = NULL;
    }
    result->plist = bucket;
    result->length = length;
    return result;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    int hash_value = hashmap->hash_func(key);
    int index = hash_value % hashmap->length;
    node_t* bucket = hashmap->plist[index];
    node_t* node = NULL;
    node_t* prev_node = NULL;
    size_t string_size = 0;
    while (bucket != NULL) {
        if (strcmp(bucket->key, key) == 0) {
            return FALSE;
        }
        prev_node = bucket;
        bucket = bucket->next;
    }
    node = malloc(sizeof(node_t));
    string_size = strlen(key);
    node->key = malloc(sizeof(char) * (string_size + 1));
    memcpy(node->key, key, string_size + 1);
    node->next = NULL;
    node->value = value;
    if (prev_node == NULL) {
        hashmap->plist[index] = node;
    } else {
        prev_node->next = node;
    }
    return TRUE;
}

int get_value(hashmap_t* hashmap, const char* key)
{
    int hash_value = hashmap->hash_func(key);
    int index = hash_value % hashmap->length;
    node_t* bucket = hashmap->plist[index];
    while (bucket != NULL) {
        if (strcmp(bucket->key, key) == 0) {
            return bucket->value;
        }
        bucket = bucket->next;
    }
    return -1;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    int hash_value = hashmap->hash_func(key);
    int index = hash_value % hashmap->length;
    node_t* bucket = hashmap->plist[index];
    while (bucket != NULL) {
        if (strcmp(bucket->key, key) == 0) {
            bucket->value = value;
            return TRUE;
        }
        bucket = bucket->next;
    }
    return FALSE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    int hash_value = hashmap->hash_func(key);
    int index = hash_value % hashmap->length;
    node_t* bucket = hashmap->plist[index];
    node_t* prev_node = NULL;
    while (bucket != NULL) {
        if (strcmp(bucket->key, key) == 0) {
            if (prev_node == NULL) {
                hashmap->plist[index] = bucket->next;
            } else {
                prev_node->next = bucket->next;
            }
            free(bucket->key);
            free(bucket);
            return TRUE;
        }
        prev_node = bucket;
        bucket = bucket->next;
    }
    return FALSE;
}

void destroy(hashmap_t* hashmap)
{
    node_t* bucket = NULL;
    size_t i = 0;
    for (i = 0; i < hashmap->length; ++i) {
        bucket = hashmap->plist[i];
        while (bucket != NULL) {
            node_t* temp = bucket;
            bucket = bucket->next;
            free(temp->key);
            free(temp);
        }
    }
    free(hashmap->plist);
    free(hashmap);
}
