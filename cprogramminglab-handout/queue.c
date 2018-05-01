/* 
 * Cde for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    /* Remember to handle the case if malloc returned NULL */
    queue_t* new_queue = (queue_t *)malloc(sizeof(queue_t));
    if (new_queue == NULL) {
        printf("ERROR: out of memory\n");
        return NULL;
    }
    new_queue->head = NULL;
    new_queue->tail = NULL; 
    new_queue->size = 0;
    return new_queue;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Remember to free the queue structue and list elements */
    if (q == NULL) {
        return;
    }
    list_ele_t* tmp = q->head;
    while (tmp != NULL) {
        q->head = q->head->next;
        free(tmp);
        tmp = q->head;
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }
    /* What if malloc returned NULL? */
    list_ele_t* new_node = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (new_node == NULL) {
        return false;
    }
    new_node->value = v;
    new_node->next = NULL;
    if (q->size == 0) {
        q->tail = new_node;
    } else {
        new_node->next = q->head;
    }

    q->head = new_node;
    q->size += 1;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    list_ele_t* new_node = (list_ele_t *) malloc(sizeof(list_ele_t));
    if (new_node == NULL) {
        return false;
    }   
    new_node->value = v;
    new_node->next = NULL;
    if (q->size == 0) {
       q->head = new_node; 
    } else {
       q->tail->next = new_node;
    }
    q->tail = new_node;
    q->size += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if (q == NULL || q->size == 0) {
        return false;
    }
    list_ele_t* first = q->head;
    int val = first->value;
    if (vp != NULL) {
        *vp = val;
    }
    q->head = first->next;
    free(first);
    q->size -= 1;
    return true;
}


/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size == 0) {
       return;
    }
    list_ele_t* new_head = q->tail;
    list_ele_t* new_tail = q->head;
    list_ele_t* prev = q->head;
    list_ele_t* current = q->head->next;
    while (current != NULL) {
        list_ele_t* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    q->head = new_head;
    q->tail = new_tail;
    q->tail->next = NULL;
}

