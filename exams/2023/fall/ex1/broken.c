#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char value[128];
    struct node * next;
} Elem;

int listdelete(char value[], Elem ** head) {
    Elem * tmp;

    while (*head && strcmp((*head)->value, value)) {
        head = &((*head)->next);
    }

    if (*head) {
        tmp=*head;
        *head = tmp->next;
        free(tmp);
        return 1;
    }
    return -1;
}

int listadd(char value[], Elem ** head) {
    Elem * new = malloc(sizeof(Elem));
    if (new == NULL) {
        return 0;
    }
    Elem * tmp;
    tmp=*head;
    *head=new;
    new->next=tmp;
    strncpy(new->value, value, 127);
    return 1;
}

void listprint(Elem * list) {
  while(list) {
    printf("%s -> ", list->value);
    list = list->next;
  }
  printf("NULL\n");
}

int main() {

    Elem elem1 = {"bruh", NULL};
    Elem * head = &elem1;

    listadd("yee", &head);
    listadd("yesss!", &head);
    listprint(head);
    printf("listdelete: %d\n", listdelete("bruh", &head));
    listprint(head);
    return 0;
}

