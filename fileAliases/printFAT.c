//
//  printFAT.c
//  fileAliases
//
//  Created by Артем Шарапов on 28.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "print.h"
#include <stdio.h>

void printFAT(FileSystem* system) {
    for (int i = 0; i < system->superblock.FATsize / 8; ++i) {
        printf("Номер блока: %d " , system->FAT[i][0]);
        if (system->FAT[i][1] == 0) {
            printf("Состояние: блок свободен\n");
        }
        else {
            if (system->FAT[i][1] != EOC && system->FAT[i][1] != BROKEN) {
                printf("Состояние: блок занят файлом и не является последним блоком файла\n");
            }
            else {
                if (system->FAT[i][1] == EOC) {
                    printf("Состояние: блок является последним блоком файла\n");
                }
                else {
                    if (system->FAT[i][1] == BROKEN ) {
                        printf("Состояние: блок поврежден \n");
                    }
                    else {
                        printf("Некорректное значение состояния блока\n");
                        return;
                    }
                }
            }
        }
    }
}
