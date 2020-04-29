//
//  List.h
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#pragma once
#include "File.h"

typedef struct NodeList {
    struct Node {
        File data;
        struct NodeList* headOfChildsList;
    }* data;
    struct NodeList* next;
} NodeList;

typedef struct Node Node;

NodeList* initList(void); //Init the head of list
void appendList(NodeList* head, Node* data);
void printList(NodeList* head);
void freeList(NodeList* head);

Node getValueAtIndex (NodeList* head, unsigned index);
