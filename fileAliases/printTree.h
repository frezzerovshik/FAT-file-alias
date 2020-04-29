//
//  printTree.h
//  fileAliases
//
//  Created by Артем Шарапов on 29.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "List.h"
#include "FileSystem.h"

void makeTree (FileSystem* system);
void printTree (Node* root);
void deleteTree (Node* root);
void appendTree (Node* root, FileSystem* system);
