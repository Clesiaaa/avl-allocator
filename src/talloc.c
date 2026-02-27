#include <stdio.h>
#include <unistd.h>
#include "../include/talloc.h"
#include "../include/block.h"
#include "../include/tools.h"

block_t *heap_start = NULL;
void *t_alloc(size_t size)
{   
    block_t *current = heap_start;
    
    if (current == NULL) {
        block_t *new_block = sbrk(size + sizeof(block_t));
        new_block->size = size;
        new_block->is_free = 0;
        new_block->next = NULL;
        heap_start = new_block;
        return (char*)heap_start + sizeof(block_t);
    }   

    while (current->next != NULL) {
        if (current->is_free && (size <= current->size)) {
            return (char*)current + sizeof(block_t);   
        }
        current = current->next;
    }

    if (current->is_free && (size <= current->size)) {
            return (char*)current + sizeof(block_t);   
        }   

    block_t *new_block = sbrk(size + sizeof(block_t));;
    new_block->is_free = 0;
    new_block->next = NULL;
    current->next = new_block;
    return (char*)current->next + sizeof(block_t);
}

node_t *heap_startx = NULL;
void *t_allocx(size_t size)
{
    node_t *current_node = heap_startx;

    if (current_node == NULL) {
        node_t *new_node = sbrk(size + sizeof(node_t));
        new_node->left = NULL;
        new_node->is_free = 0;
        new_node->size = size;
        new_node->right = NULL;
        heap_startx = new_node;
        return (char*)heap_startx + sizeof(node_t);
    }
    
    uint8_t pos = 0; //0 left 1 right
    uint8_t found = 0;
    while (!found) {
        
        if (current_node->is_free && (size <= current_node->size)) {
            return (char*)current_node + sizeof(node_t);
        } else if (size < current_node->size) {
            if (current_node->left == NULL) {
                found = 1;
                break;
            }
            current_node = current_node->left;
        } else {
            if (current_node->right == NULL) {
                pos = 1;
                found = 1;
                break;
            }
            current_node = current_node->right;
        } 
    }

    node_t *new_node = sbrk(size + sizeof(node_t));
    new_node->is_free = 0;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->size = size;

    if (pos){
        current_node->right = new_node;
        current_node = current_node->right;
        return (char*)current_node + sizeof(node_t);   
    } else {
        current_node->left = new_node;
        current_node = current_node->left;
        return (char*)current_node + sizeof(node_t);   
    }
}