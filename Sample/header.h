typedef struct node {
  int elem;
  struct node *next;
} Node;

typedef void (FPTR)(Node *);

void foo(Node *n);
void goo(Node *n);
