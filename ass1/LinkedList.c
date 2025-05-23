/*
 * File: LinkedList.c
 * File Created: Thursday, 2nd April 2020 5:54:10 pm
 * Author: Jonathon Winter
 * -----
 * Last Modified: Tuesday, 20th May 2025 2:16:00 pm
 * Modified By: James Vuong
 * -----
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

/* Definitions for Linked List structures */

/* Function to create a new linked list */
LinkedList *createLinkedList() {
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        return NULL; /* Memory allocation failed */
    }
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}

/* Function to insert a new node at the start of the list */
void insertStart(LinkedList *list, void *data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (newNode == NULL) {
        return; /* Memory allocation failed */
    }
    newNode->data = data;
    newNode->next = list->head;
    newNode->prev = NULL;

    if (list->head != NULL) {
        list->head->prev = newNode;
    } else {
        list->tail = newNode;
    }
    list->head = newNode;
    list->count++;
}

/* Function to insert a new node at the end of the list */
void insertLast(LinkedList *list, void *data) {
    LinkedListNode *newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (newNode == NULL) {
        return; /* Memory allocation failed */
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = list->tail;

    if (list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;
    list->count++;
}

/* Function to remove the first node from the list */
void *removeStart(LinkedList *list) {
    LinkedListNode *node;
    void *data;

    if (list->count == 0) {
        return NULL; /* List is empty */
    }

    node = list->head;
    data = node->data;

    list->head = node->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }

    free(node);
    list->count--;
    return data;
}

/* Function to remove the last node from the list */
void *removeLast(LinkedList *list) {
    LinkedListNode *node;
    void *data;

    if (list->count == 0) {
        return NULL; /* List is empty */
    }

    node = list->tail;
    data = node->data;

    list->tail = node->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }

    free(node);
    list->count--;
    return data;
}

/* Function to print the linked list */
void printLinkedList(LinkedList *list, void (*printFunc)(void *)) {
    LinkedListNode *current = list->head;
    while (current != NULL) {
        printFunc(current->data);
        current = current->next;
    }
}

/* Function to free the entire linked list */
void freeLinkedList(LinkedList *list, void (*freeFunc)(void *)) {
    LinkedListNode *current = list->head;
    LinkedListNode *next;

    while (current != NULL) {
        next = current->next;
        if (freeFunc != NULL) {
            freeFunc(current->data);
        }
        free(current);
        current = next;
    }

    free(list);
}