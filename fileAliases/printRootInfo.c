//
//  printRootInfo.c
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "print.h"
#include <stdio.h>

void printRootInfo(FileSystem* system) {
    printf("Имя файла: %s   Размер: %u\n" , system->root->nameOfFile , system->root->size);
}
