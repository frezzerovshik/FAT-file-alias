//
//  memoryDealloc.c
//  fileAliases
//
//  Created by Артем Шарапов on 30.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include "memoryDealloc.h"
#include <stdlib.h>
#include "readingFile.h"

void memory_dealloc(FileSystem* system, FILE* image) {
    free(system->root);
    for (int i = 0; i < system->superblock.FATsize / 8; ++i) {
        free(system->FAT[i]);
    }
    free(system->FAT);
    for (int i = 0; i < (fileSize(image) - (sizeof(system->superblock) + system->superblock.FATsize + system->superblock.rootSize))/system->superblock.sizeOFBlock; ++i) {
        free(system->data[i]);
    }
    free(system->data);
    free(system);
}
