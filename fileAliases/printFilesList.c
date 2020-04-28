//
//  printFilesList.c
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "print.h"
#include <stdio.h>

void printFilesList(FileSystem* system) {
    printf("ID\tНаименование\n");
    for (int i = 0; i < system->superblock.FATsize / 8; ++i) {
        printf("%d\t%s\n" , system->root->numberOfFirstFileBlock , system->root->nameOfFile);
    }
}
