#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT,
    CHAR
} Type;

typedef struct Node {
    void *value;
    Type type;
    struct Node *next;
    struct Node *prev;
} Node;

// NOTE const qualifier fix
#define New(VALUE)                                              \
    ({                                                          \
        void *val = malloc(sizeof(__typeof__(VALUE)));          \
        if (val == NULL) {                                      \
            perror("Failed to allocate memory");                \
            exit(EXIT_FAILURE);                                 \
        }                                                       \
        if (sizeof(__typeof__(VALUE)) == sizeof(int)) {         \
            *(int *)val = (int)(VALUE);                         \
        } else if (sizeof(__typeof__(VALUE)) == sizeof(char)) {	\
            *(char *)val = (char)(VALUE);                       \
        }                                                       \
        Node *node = malloc(sizeof(Node));                      \
        if (node == NULL) {                                     \
            perror("Failed to allocate memory");                \
            exit(EXIT_FAILURE);                                 \
        }                                                       \
        node->value = val;                                      \
        node->type = _Generic((VALUE), int: INT, char: CHAR);	\
        node->next = NULL;                                      \
        node->prev = NULL;                                      \
        node;                                                   \
    })

Node *head(Node *n) {
    while (n != NULL && n->prev != NULL) {
        n = n->prev;
    }
    return n;
}

Node *tail(Node *n) {
    return n->next;
}

Node *last(Node *n) {
    while (n != NULL && n->next != NULL) {
        n = n->next;
    }
    return n;
}

void freeNode(Node *n) {
    if (n == NULL)
        return;
    freeNode(n->next);
    free(n->value);
    free(n);
}

void freeList(Node *n) {
    freeNode(head(n));
}

void printNode(Node *n) {
    if (n == NULL) {
        printf("%p[SEGFAULT]\n", n);
        return;
    }

    printf("(%p)[", n);
    if (n->type == INT) {
        printf("%d", *(int *)n->value);
    } else if (n->type == CHAR) {
        printf("'%c'", *(char *)n->value);
    }
    printf("] -> ");
    printNode(n->next);
}

void printList(Node *n) {
    printNode(head(n));
}


Node *string(const char *str) {
    if (str == NULL || *str == '\0') {
        return NULL;
    }
  
    Node *head = NULL;
    Node *tail = NULL;

    while (*str) {
        Node *node = New(*str);
    
        if (head == NULL) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    
        str++;
    }
  
    return head;
}

// TODO macro to assign n->value = anything

int main() {
    Node *n1 = New((char)'b'); // NOTE funny C
    Node *n2 = New(2);
    Node *n3 = New(3);

    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;

    printNode(n3);
    printList(n3);

    printNode(head(n3));
    printNode(tail(n1));

    Node *s = string("Hello!");
    printNode(s);

    freeList(n1);
    return 0;
}

