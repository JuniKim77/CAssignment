#include "todo_list.h"

todo_list_t* init_todo_list_malloc(size_t max_size)
{
    todo_list_t* result = malloc(sizeof(todo_list_t));
    result->capacity = max_size;
    result->size = 0;
    result->phead = NULL;
    return result;
}

void dispose(todo_list_t* todo_list)
{
    todo_node_t* current;
    todo_node_t* next;
    if (todo_list == NULL) {
        return;
    }
    current = todo_list->phead;
    if (current == NULL) {
        goto free_todo_list;
    }
    next = current->next;
    while (next != NULL) {
        free(current->name);
        free(current);
        current = next;
        next = next->next;
    }
    free(current->name);
    free(current);
free_todo_list:
    free(todo_list);
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    todo_node_t* compare_node;
    todo_node_t* prev_node;
    todo_node_t* new_node;
    size_t size = 0;
    if (todo_list == NULL) {
        return false;
    }
    size = strlen(task);
    compare_node = todo_list->phead;
    prev_node = compare_node;
    if (todo_list->capacity == todo_list->size) {
        return false;
    }
    todo_list->size++;
    new_node = malloc(sizeof(todo_node_t));
    new_node->name = malloc(sizeof(char) * (size + 1));
    memcpy(new_node->name, task, size + 1);
    new_node->priority = priority;
    new_node->next = NULL;
    if (todo_list->size == 1) {
        todo_list->phead = new_node;
        return true;
    }
    while (compare_node != NULL) {
        if (compare_node->priority < priority) {
            break;
        }
        prev_node = compare_node;
        compare_node = compare_node->next;
    }
    if (prev_node == compare_node) {
        new_node->next = compare_node;
        todo_list->phead = new_node;
    } else {
        new_node->next = prev_node->next;
        prev_node->next = new_node;
    }
    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    todo_node_t* complete_node;
    if (todo_list == NULL) {
        return false;
    }
    if (todo_list->size == 0) {
        return false;
    }
    complete_node = todo_list->phead;
    todo_list->phead = complete_node->next;
    free(complete_node->name);
    free(complete_node);
    todo_list->size--;
    return true;
}

const char* peek_or_null(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return NULL;
    }
    if (todo_list->size == 0) {
        return NULL;
    }
    return todo_list->phead->name;
}

size_t get_count(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return 0;
    }
    return todo_list->size;
}

bool is_empty(todo_list_t* todo_list)
{
    if (todo_list == NULL) {
        return true;
    }
    if (todo_list->size == 0) {
        return true;
    } else {
        return false;
    }
}
