//
//  printSuperblockInfo.c
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "print.h"
#include <stdio.h>

void printSuperclassInfo (FileSystem* system) {
    printf("Информация о файловой системе:\n Размер блока: %u байт\nРазмер FAT: %u байт\nРазмер Root: %u байт\nСдвиг шифрования: %u байт\n" , system->superblock.sizeOFBlock, system->superblock.FATsize,system->superblock.rootSize,system->superblock.cypherShift);
}
