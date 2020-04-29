//
//  printTree.c
//  fileAliases
//
//  Created by Артем Шарапов on 29.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "printTree.h"
#include <stdlib.h>
#include "print.h"
#include <string.h>

#define SUBDIRECTORY 0x2

void makeTree (FileSystem* system) {
    Node* root = (Node*)malloc(sizeof(Node));
    strcpy(root->data.nameOfFile, "/           ");
    root->data.attributes = SUBDIRECTORY;
    root->childs = (Node**)malloc(system->superblock.rootSize * sizeof(Node*));
    for (int i = 0; i < system->superblock.rootSize; ++i) {
        root->childs[i] = (Node*)malloc(sizeof(Node));
        root->childs[i]->data = system->root[i];
        root->childs[i]->childs = NULL;
        appendTree(root->childs[i]);
    }
}
void printTree (Node* root) {
    
}
void deleteTree (Node* root) {
    
}
void appendTree(Node* root, FileSystem* system) {

}
