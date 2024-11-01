#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

Node *new(int value) {
  Node *n = malloc(sizeof(Node));
  n->value = value;
  n->next = NULL;
  return n;
}

void freeNode(Node *n) {
  if (!n) return;
  freeNode(n->next);
  free(n);
}

Node *appendTail(Node *head, int value) {
  Node *n  = malloc(sizeof(Node));
  n->value = value;
  n->next  = NULL;
    
  if (head == NULL) {
    head = n;
  }
  else {
    Node *p = head;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = n;
  }
    
  return head;
}

Node *appendHead(Node *head, int value) {
  Node *n = malloc(sizeof(Node));
  n->value = value;
  n->next = head;
  return n;
}

void print(Node *n) {
  if (n == NULL) {
    printf("%p[SEGFAULT]\n", n);
    return;
  }
  
  printf("(%p)[%i] -> ", n, n->value);
  print(n->next);
}

Node *head(Node *n) {
  return n;
}

Node *tail(Node *n) {
  if (!n) return NULL;
  return n->next;
}


int main() {
  Node *n1 = new(1);
  Node *n2 = new(2);
  Node *n3 = new(3);
  Node *n4 = new(4);


  n1->next = n2;
  n2->next = n3;
  n3->next = n4;
  
  print(n1);
  
  Node *newHead = appendHead(n1, 5);
  print(newHead);
  
  freeNode(newHead);
}
