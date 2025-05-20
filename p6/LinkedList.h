#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedListNode {
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev; // For double-linked lists
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* head;
    LinkedListNode* tail;
    int count;
} LinkedList;

LinkedList* createLinkedList();
void insertStart(LinkedList* list, void* data);
void insertLast(LinkedList* list, void* data);
void* removeStart(LinkedList* list);
void* removeLast(LinkedList* list);
void printLinkedList(LinkedList* list, void (*printFunc)(void*));
void freeLinkedList(LinkedList* list, void (*freeFunc)(void*));

#endif