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

NodeList* initList(void) {
    NodeList* head = (NodeList*)malloc(sizeof(NodeList));
    head->data = NULL;
    head->next = NULL;
    return head;
}

void appendList(NodeList* head, Node* data) {
    NodeList* tail = head;
    while (tail->next != NULL)
        tail = tail->next;
    NodeList* newNode = (NodeList*)malloc(sizeof(NodeList));
    newNode->data = data;
    newNode->next = NULL;
    tail->next = newNode;
}

void printList(NodeList* head) {
    NodeList* i = head;
    while (i != NULL) {
        //printf("%s" , i->data);
        i = i->next;
    }
}

void freeList(NodeList* head) {
    NodeList* i = head;
    while (i != NULL) {
        NodeList* temp = i->next;
        free(i);
        i = temp;
    }
}

Node getValueAtIndex (NodeList* head, unsigned index) {
    int i = 0;
    NodeList* temp = head;
    while (temp != NULL) {
        if (i != index) {
            temp = temp->next;
            i++;
        }
        else {
            return *(temp->data);
        }
    }
    exit(1);
}
