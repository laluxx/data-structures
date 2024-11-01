#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

Node *new(int value) {
    Node *n = malloc(sizeof(Node));
    n-> value = value;
    n-> left = NULL;
    n-> right = NULL;
    return n;
}

int max(int first, int second) {
    if (first > second) {
        return first;
    } else {
        return second;
    }
}

int depth(Node *n) {
    if (!n) return 0;
    
    int ld = depth(n->left);
    int rd = depth(n->right);

    return 1 + max(ld, rd);
}

int sum(Node *n) {
    if (!n) return 0;
    return n->value + sum(n->left) + sum(n->right);
}

bool find(Node *n, int num) {
    if (!n) return false;
    if (n->value == num) return true;
    return find(n->left, num) || find(n->right, num);
}


void render(Node *root) {
    if (!root) return;

    char buffer[1024 * 100] = ""; // TODO Calculate the buffer based on the depth(root)

    typedef struct {
        Node *node;
        char prefix[1024];
        int isTail;
    } StackNode;

    void renderHelper(Node *node, char *prefix, int isTail) {
        char temp[1024];

        if (node->right != NULL) {
            char newPrefix[1024];
            sprintf(newPrefix, "%s%s", prefix, isTail ? "│   " : "    ");
            renderHelper(node->right, newPrefix, 0);
        }

        sprintf(temp, "%s%s%d\n", prefix, isTail ? "└── " : "┌── ", node->value);
        strcat(buffer, temp);

        if (node->left != NULL) {
            char newPrefix[1024];
            sprintf(newPrefix, "%s%s", prefix, isTail ? "    " : "│   ");
            renderHelper(node->left, newPrefix, 1);
        }
    }

    renderHelper(root, "", 1);
    printf("%s", buffer);
}




void freeTree(Node *n) {
    if (!n) return;
    freeTree(n->left);
    freeTree(n->right);
    free(n); // NOTE from the bottom up
}


int main() {
    Node *n1 = new(1);
    Node *n2 = new(2);
    Node *n3 = new(3);
    Node *n4 = new(4);
    Node *n5 = new(5);
    Node *n6 = new(6);
    Node *n7 = new(7);

    n1->left  = n2;
    n1->right = n3;
    n2->left  = n4;
    n2->right = n5;
    n3->left  = n6;
    n3->right = n7;


    printf("size of node = %i bytes\n", sizeof(Node));
    
    int d = depth(n1);
    printf("depth = %i\n", d);

    int s = sum(n1);
    printf("sum = %i\n", s);



    int num = 7;
    bool found = find(n1, num);
    printf("found %d = %s\n", num, found ? "true" : "false");

    render(n1);

    freeTree(n1);
    return 0;
}
