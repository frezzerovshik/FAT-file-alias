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

long int fileSize( FILE *fp ) {
   long int savePos, sizeOfFile;
   savePos = ftell( fp );
   fseek( fp, 0L, SEEK_END );
   sizeOfFile = ftell( fp );
   fseek( fp, savePos, SEEK_SET );
   return( sizeOfFile );
 }

FileSystem* readingFile(const char *path) {
    FileSystem* data = (FileSystem*)malloc(sizeof(FileSystem));
    FILE* image = fopen(path, "rb");
    if (image == NULL) {
        printf("Проблема с открытием входного файла\n");
        exit(1);
    }
    fread(data->superblock.sizeOFBlock, sizeof(data->superblock.sizeOFBlock), 1, image);
    fread(data->superblock.FATsize, sizeof(data->superblock.FATsize), 1, image);
    fread(data->superblock.rootSize, sizeof(data->superblock.rootSize), 1, image);
    fread(data->superblock.cypherShift, sizeof(data->superblock.cypherShift), 1, image);
    
    int rows = data->superblock.FATsize / 8; //Количество строк в FAT
    
    int numOfBlocks = (fileSize(image) - (sizeof(data->superblock) + data->superblock.FATsize + data->superblock.rootSize))/data->superblock.sizeOFBlock; //Расчет количества блоков данных в файловой системе
    //ЧислоБлоков = (РазмерФайла - (РазмерСуперблока + РазмерFAT + РазмерRoot))/РазмерОдногоБлока (Байт)
    data->root = (File*)malloc(data->superblock.rootSize * sizeof(File)); //Выделение памяти под корневой каталог
    
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
    for (int i = 0; i < data->superblock.rootSize; ++i) {
        fread(data->root[i].nameOfFile, sizeof(data->root[i].nameOfFile[i]), sizeof(data->root[i].nameOfFile), image);
        fread(data->root[i].numberOfFirstFileBlock, sizeof(data->root[i].numberOfFirstFileBlock), 1, image);
        fread(data->root[i].attributes, sizeof(data->root[i].attributes), 1, image);
        fread(data->root[i].dateTime, sizeof(data->root[i].dateTime), 1, image);
        fread(data->root[i].size, sizeof(data->root[i].size), 1, image);
    }
    
    //Чтение блоков данных
    for (int i =0; i < numOfBlocks; ++i) {
            fread(data->data[i], 1, data->superblock.sizeOFBlock, image);
    }
    return data;
}


