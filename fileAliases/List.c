//
//  List.c
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "List.h"
#include <stdlib.h>
#include <stdio.h>

Node* initList(void) {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = NULL;
    head->next = NULL;
    return head;
}

void appendList(Node* head, char* data) {
    Node* tail = head;
    while (tail->next != NULL)
        tail = tail->next;
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    tail->next = newNode;
}

void printList(Node* head) {
    Node* i = head;
    while (i != NULL) {
        printf("%s" , i->data);
        i = i->next;
    }
}

void freeList(Node* head) {
    Node* i = head;
    while (i != NULL) {
        Node* temp = i->next;
        free(i);
        i = temp;
    }
}
