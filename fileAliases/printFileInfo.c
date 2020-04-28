//
//  printFileInfo.c
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "print.h"
#include <stdio.h>

void printFileInfo(FileSystem* system, int fileId) {
    for (int i = 0; i < system->superblock.rootSize / sizeof(File); ++i) {
        if (system->root[i].numberOfFirstFileBlock == fileId) {
            //Добавит маску для распознавания даты и времени
        }
    }
}
