//
//  printTextFile.c
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#pragma once
#include <stdio.h>
#include "print.h"

#define _true 1

void printTextFile(FileSystem* system, int numberOfFirstFileBlock) {
    int i = numberOfFirstFileBlock;
    while (_true) {
        printf("%s", system->data[system->FAT[i][0]]);
        if (system->FAT[i][1] != EOC)
            i = system->FAT[i][1];
        else
            break;
    }
}
