//
//  List.h
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#pragma once

typedef struct Node {
    char *data; //Необходимо выделять память равную размеру блока
    struct Node* next;
} Node;

Node* initList(void); //Init the head of list
void appendList(Node* head, char* data);
void printList(Node* head);
void freeList(Node* head);
