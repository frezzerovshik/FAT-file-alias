//
//  readingFile.c
//  fileAliases
//
//  Created by Артем Шарапов on 27.04.2020.
//  Copyright © 2020 Hooba-booba. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "readingFile.h"

FileSystem* readingFile(const char *path) {
    FileSystem* data = (FileSystem*)malloc(sizeof(FileSystem));
    FILE* image = fopen(path, "r");
    if (image == NULL) {
        printf("Проблема с открытием входного файла\n");
        exit(1);
    }
    fread(data->superblock.sizeOFBlock, sizeof(unsigned), 1, image);
    fread(data->superblock.FATsize, sizeof(unsigned), 1, image);
    fread(data->superblock.rootSize, sizeof(unsigned), 1, image);
    fread(data->superblock.cypherShift, sizeof(unsigned), 1, image);
    
    int rows = data->superblock.FATsize / 8; //Количество строк в FAT
    
    int numOfBlocks = (MAX_FILE_SIZE - (sizeof(data->superblock) + data->superblock.FATsize + data->superblock.rootSize))/data->superblock.sizeOFBlock; //Расчет количества блоков данных в файловой системе
    //ЧислоБлоков = (РазмерФайла - (РазмерСуперблока + РазмерFAT + РазмерRoot))/РазмерОдногоБлока (Байт)
    data->root = (File*)malloc(data->superblock.rootSize); //Выделение памяти под корневой каталог
    
    //Выделение памяти под FAT
    data->FAT = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i)
        data->FAT[i] = (int*)malloc(2 * sizeof(int));
    
    //Выделение памяти для данных
    data->data = (char**)malloc(numOfBlocks * sizeof(char*));
    for (int i = 0; i < numOfBlocks; ++i)
        data->data[i] = (char*)malloc(data->superblock.sizeOFBlock);
    
    //Чтение FAT
    for (int i = 0; i < numOfBlocks; ++i) {
            fread(data->FAT[i], 4, 2, image);
    }
    
    //Чтение корневого каталога
    for (int i = 0; i < data->superblock.rootSize / sizeof(File); ++i) {
        fread(data->root[i].nameOfFile, 1, 12, image);
        fread(data->root[i].numberOfFirstFileBlock, 4, 1, image);
        fread(data->root[i].attributes, 4, 1, image);
        fread(data->root[i].dateTime, 4, 1, image);
        fread(data->root[i].size, 4, 1, image);
    }
    
    //Чтение блоков данных
    for (int i =0; i < numOfBlocks; ++i) {
            fread(data->data[i], 1, data->superblock.sizeOFBlock, image);
    }
    return data;
}


